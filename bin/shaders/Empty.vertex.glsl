#version 400 core

in layout(location=0) vec4 coords;
in layout(location=1) vec4 color;


uniform mat4 PROJ_MAT;

uniform mat4 MVP;

const float deg = 45*3.14/180;
uniform mat4 rotX = 
{
    vec4(1, 0, 0, 0),
	vec4(0, cos(deg), -sin(deg), 0),
	vec4(0, sin(deg), cos(deg), 0),
	vec4(0, 0, 0, 1)
};
out vec4 color_output;

mat4 LookAtRH( vec3 eye, vec3 target, vec3 up )
{
    vec3 zaxis = eye - target; 
	zaxis = zaxis/length(zaxis);   // The "forward" vector
    vec3 xaxis = cross(up, zaxis); // The "right" vector.
	xaxis = xaxis/length(xaxis);
    vec3 yaxis = cross(zaxis, xaxis);     // The "up" vector.
 
    // Create a 4x4 orientation matrix from the right, up, and forward vectors
    // This is transposed which is equivalent to performing an inverse 
    // if the matrix is orthonormalized (in this case, it is).
    mat4 orientation = mat4(
       vec4( xaxis.x, yaxis.x, zaxis.x, 0 ),
       vec4( xaxis.y, yaxis.y, zaxis.y, 0 ),
       vec4( xaxis.z, yaxis.z, zaxis.z, 0 ),
       vec4(   0,       0,       0,     1 )
    );
     
    // Create a 4x4 translation matrix.
    // The eye position is negated which is equivalent
    // to the inverse of the translation matrix. 
    // T(v)^-1 == T(-v)
    mat4 translation = mat4(
        vec4(   1,      0,      0,   0 ),
        vec4(   0,      1,      0,   0 ), 
        vec4(   0,      0,      1,   0 ),
        vec4(-eye.x, -eye.y, -eye.z, 1 )
    );
 
    // Combine the orientation and translation to compute 
    // the final view matrix
    return ( orientation * translation );
}

void main()
{
	float pi = 3.14159265358979323846264;
    float FoV = 1.f/tan((180.0f/2.f)*pi/180.f);
    float aspect = 800.f/600.f;
    float N = 0.1f;
    float F = 3.0f;

	vec3 eye = vec3(0.f, 0.f, -1.2f);
	vec3 target = vec3(0.f, 0.f, 1.f);
	vec3 up = vec3(0.f, 1.f, 0.f);
	mat4 vm = LookAtRH(eye, target, up);


    mat4 view = mat4(
        vec4(+1.0f, +0.0f, +0.0f, +0.0f),
		vec4(+0.0f, +1.0f, +0.0f, +0.0f),
		vec4(+0.0f, +0.0f, +1.0f, +0.0f),
		vec4(+0.0f, +0.0f, +0.0f, +1.0f));
    
	mat4 proj = mat4(
        vec4(FoV/aspect,  0,            0,           0),
		vec4(0,         FoV,            0,           0),
		vec4(0,           0, (N+F)/(N-F), (2*N*F)/(N-F)),
		vec4(0,           0,           -1,           0));


    gl_Position = PROJ_MAT * vm *  MVP * rotX *  coords;
	color_output = color;
    //color_output = (gl_Position + 1.0f)/2.0f;
	//color_output.z = (color_output.z + 1.0f) / 2.0f;
	//gl_Position = MVP * rotX * coords;
}







