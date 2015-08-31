#version 400 core

in vec4 coords;
in vec4 color;

uniform mat4 MVP = {
    vec4(1, 0, 0, 0),
	vec4(0, 1, 0, 0),
	vec4(0, 0, 1, 0),
	vec4(0, 0, 0, 1)};

out vec4 color_output;

void main()
{
    gl_Position = MVP * coords;
    color_output = color;
}







