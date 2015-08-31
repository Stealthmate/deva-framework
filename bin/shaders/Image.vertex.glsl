#version 400 core

in vec4 coords;
in vec4 tex_coords;

uniform sampler2D samp;

uniform mat4 MVP = {
    vec4(1, 0, 0, 0),
	vec4(0, 1, 0, 0),
	vec4(0, 0, 1, 0),
	vec4(0, 0, 0, 1)};

out vec4 tex_output;

void main()
{
    gl_Position = coords;
    tex_output = tex_coords;
}