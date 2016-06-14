const char * FRAGMENT_SHADER =
R"shader(

#version 400 core

in vec4 tex_output;
out vec4 final_color;

uniform sampler2D samp;

uniform mat4 MVP;

void main()
{
	vec2 t = tex_output.xy;
	t.x = (t.x+1)/2;
	t.y = (t.y+1)/2;
	final_color = texture(samp, t);
}

)shader";