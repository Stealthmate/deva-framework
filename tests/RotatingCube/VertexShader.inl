const char* VERTEX_SHADER = 
R"shader("

#version 400 core

in layout(location = 0) vec4 coords;
in layout(location = 1) vec4 color;

uniform mat4 PROJ_MAT =
{
	vec4(1, 0, 0, 0),
	vec4(0, 1, 0, 0),
	vec4(0, 0, 1, 0),
	vec4(0, 0, 0, 1)
};

uniform mat4 MVP =
{
	vec4(1, 0, 0, 0),
	vec4(0, 1, 0, 0),
	vec4(0, 0, 1, 0),
	vec4(0, 0, 0, 1)
};

const float deg = 45 * 3.14 / 180;
uniform mat4 rotX =
{
	vec4(1, 0, 0, 0),
	vec4(0, cos(deg), -sin(deg), 0),
	vec4(0, sin(deg), cos(deg), 0),
	vec4(0, 0, 0, 1)
};

out vec4 color_output;

mat4 LookAtRH(vec3 eye, vec3 target, vec3 up)
{
	vec3 zaxis = eye - target;
	zaxis = zaxis / length(zaxis);   // The "forward" vector
	vec3 xaxis = cross(up, zaxis); // The "right" vector.
	xaxis = xaxis / length(xaxis);
	vec3 yaxis = cross(zaxis, xaxis);     // The "up" vector.

										  // Create a 4x4 orientation matrix from the right, up, and forward vectors
										  // This is transposed which is equivalent to performing an inverse 
										  // if the matrix is orthonormalized (in this case, it is).
	mat4 orientation = mat4(
		vec4(xaxis.x, yaxis.x, zaxis.x, 0),
		vec4(xaxis.y, yaxis.y, zaxis.y, 0),
		vec4(xaxis.z, yaxis.z, zaxis.z, 0),
		vec4(0, 0, 0, 1)
	);

	// Create a 4x4 translation matrix.
	// The eye position is negated which is equivalent
	// to the inverse of the translation matrix. 
	// T(v)^-1 == T(-v)
	mat4 translation = mat4(
		vec4(1, 0, 0, 0),
		vec4(0, 1, 0, 0),
		vec4(0, 0, 1, 0),
		vec4(-eye.x, -eye.y, -eye.z, 1)
	);

	// Combine the orientation and translation to compute 
	// the final view matrix
	return (orientation * translation);
}

void main()
{
	vec3 eye = vec3(0.f, 0.f, -1.2f);
	vec3 target = vec3(0.f, 0.f, 1.f);
	vec3 up = vec3(0.f, 1.f, 0.f);
	mat4 vm = LookAtRH(eye, target, up);

	gl_Position = PROJ_MAT * vm *  MVP * rotX *  coords;
	color_output = color;
}

")shader";