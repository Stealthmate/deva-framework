#version 400 core

in vec4 color_output;
out vec4 final_color;

uniform mat4 MVP;

void main()
{
	final_color = color_output;
}

