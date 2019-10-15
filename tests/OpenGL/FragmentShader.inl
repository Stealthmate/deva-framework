const char* FRAGMENT_SHADER =
R"shader(

#version 400 core

in vec4 color_output;
out vec4 final_color;

void main()
{
	final_color = color_output;
}

)shader";