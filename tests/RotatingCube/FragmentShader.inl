const char* FRAGMENT_SHADER =
R"shader("

#version 400 core

in vec4 color_output;
out vec4 final_color;

uniform mat4 MVP;

void main()
{
	final_color = color_output;
	//final_color = vec4(0.f, 0.f, 1.f, 1.f);
}

")shader";