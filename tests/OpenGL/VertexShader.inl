const char* VERTEX_SHADER =
R"shader(

#version 400 core

in layout(location=0) vec4 coords;
in layout(location=1) vec4 color;

out vec4 color_output;

void main()
{
	gl_Position = coords;
	color_output = color;
}

)shader";