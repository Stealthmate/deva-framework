const char* VERTEX_SHADER =
R"shader(

#version 400 core

in vec4 coords;
in vec4 tex_coords;

uniform sampler2D samp;

out vec4 tex_output;

void main()
{
    gl_Position = coords;
    tex_output = tex_coords;
}

)shader";