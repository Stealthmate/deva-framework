#include <iostream>

#include <glbinding/gl/gl.h>
#include <glbinding/Binding.h>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "../src/Deva.hpp"

namespace
{
	using namespace DevaFramework;
	using namespace gl;
	using namespace glbinding;

	void OnKey(Window &win, Key k, InputAction ia, int modmask)
	{
		if (k == Key::KEY_ESCAPE) win.close();
	}

	int progid_shader = 0;
}




void render_text(std::string str, float x, float y, int fontsize) 
{

	FT_Library ft;

	if (FT_Init_FreeType(&ft)) {
		fprintf(stderr, "Could not init freetype library\n");
		return;
	}

	FT_Face face;

	if (FT_New_Face(ft, "testfont.ttf", 0, &face)) {
		fprintf(stderr, "Could not open font\n");
		return;
	}

	FT_Set_Pixel_Sizes(face, 0, fontsize);

	if (FT_Load_Char(face, 'X', FT_LOAD_RENDER)) {
		fprintf(stderr, "Could not load character 'X'\n");
		return;
	}
	FT_GlyphSlot g = face->glyph;

	float space = fontsize / 800.0f;

	std::vector<float> base_coords;
	std::vector<unsigned int> indices;

	float x_c = x;
	float y_c = y;

	float sx = 2 / 800.f;
	float sy = 2 / 600.f;

	for(int i = 0; i <= str.length() - 1; i++)
	{
		if (FT_Load_Char(face, str.at(i), FT_LOAD_RENDER)) {
			fprintf(stderr, "Could not load character 'X'\n");
			return;
		}

		base_coords.clear();
		indices.clear();

		base_coords.push_back(x_c);
		base_coords.push_back(y_c);
		base_coords.push_back(0.0f);
		base_coords.push_back(1.0f);
		base_coords.push_back(-1.0f);
		base_coords.push_back(-1.0f);
		base_coords.push_back(0.0f);
		base_coords.push_back(1.0f);
		base_coords.push_back(x_c);
		base_coords.push_back(y_c + g->bitmap.rows * sy);
		base_coords.push_back(0.0f);
		base_coords.push_back(1.0f);
		base_coords.push_back(-1.0f);
		base_coords.push_back(1.0f);
		base_coords.push_back(0.0f);
		base_coords.push_back(1.0f);
		base_coords.push_back(x_c + g->bitmap.width * sx);
		base_coords.push_back(y_c + g->bitmap.rows * sy);
		base_coords.push_back(0.0f);
		base_coords.push_back(1.0f);
		base_coords.push_back(1.0f);
		base_coords.push_back(1.0f);
		base_coords.push_back(0.0f);
		base_coords.push_back(1.0f);
		base_coords.push_back(x_c + (g->bitmap.width * sx));
		base_coords.push_back(y_c);
		base_coords.push_back(0.0f);
		base_coords.push_back(1.0f);
		base_coords.push_back(1.0f);
		base_coords.push_back(-1.0f);
		base_coords.push_back(0.0f);
		base_coords.push_back(1.0f);

		indices.push_back(i * 4);
		indices.push_back(i * 4 + 1);
		indices.push_back(i * 4 + 2);
		indices.push_back(i * 4 + 2);
		indices.push_back(i * 4 + 0);
		indices.push_back(i * 4 + 3);


		GLuint buffer = 0;
		glGenBuffers(1, &buffer);
		glBindBuffer(GL_ARRAY_BUFFER, buffer);
		glBufferData(GL_ARRAY_BUFFER, base_coords.size() * sizeof(float), &base_coords[0], GL_STATIC_DRAW);

		GLuint elementbuffer = 1;
		glGenBuffers(1, &elementbuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

		GLuint tb;
		glGenTextures(1, &tb);
		glBindTexture(GL_TEXTURE_2D, tb);
		glTexImage2D(GL_TEXTURE_2D,
			0, static_cast<GLint>(GL_RGBA), g->bitmap.width, g->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, g->bitmap.buffer);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);

		x_c += (g->advance.x / 64) * sx;
	}
	/*for (int i = 0;i <= indices.size() - 1; i += 6) 
	{
		std::string out = "";
		out =
			"\n[" + strm(base_coords[indices[i]*4]) + ";"
			+ strm(base_coords[indices[i]*4 + 1]) + "] ["
			+ strm(base_coords[indices[i + 1]*4]) + ";"
			+ strm(base_coords[indices[i + 1]*4 + 1]) + "] ["
			+ strm(base_coords[indices[i + 2]*4]) + ";"
			+ strm(base_coords[indices[i + 2]*4 + 1]) + "]\n"
			+ strm(base_coords[indices[i + 3]*4]) + ";"
			+ strm(base_coords[indices[i + 3]*4 + 1]) + "] ["
			+ strm(base_coords[indices[i + 4]*4]) + ";"
			+ strm(base_coords[indices[i + 4]*4 + 1]) + "] ["
			+ strm(base_coords[indices[i + 5]*4]) + ";"
			+ strm(base_coords[indices[i + 5]*4 + 1]) + "]\n";
		Logger::println(out);
	}*/
}

int main()
{

	DEVA_INIT();

	Window &wnd = Window::createWindow(800, 600, "OpenGL Display Image");
	Window::setCurrentWindow(wnd);
	wnd.setOnKeyActionCallback(OnKey);

	glbinding::Binding::initialize();

	std::string vshader = readTextFile("shaders/Image.vertex.glsl");
	std::string fshader = readTextFile("shaders/Image.fragment.glsl");

	GLuint progid = loadShaderSet(vshader, fshader);
	progid_shader = progid;
	const float triangle_coords_colors[] =
	{ -1.f, -1.f, 0.f, 1.f, //XYZW
		0.f,  1.f, 0.f, 1.f, //RGBA
		1.f, -1.f, 0.f, 1.f, //XYZW
		1.f,  0.f, 0.f, 1.f, //RGBA
		0.f,  1.f, 0.f, 1.f, //XYZW
		0.f,  0.f, 1.f, 1.f }; //RGBA

	GLuint buffer = 0;

	glUseProgram(progid);
	/*glGenBuffers(1, &buffer);
	glBindBuffer(gl::GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(float), &triangle_coords_colors[0], GL_STATIC_DRAW);
	/*
	GLuint mvp_unif = glGetUniformLocation(progid, "MVP");
	Image img = Image::loadImageFromFile("SS1.png", ImageFormat::PNG);
	GLuint tb;
	glGenTextures(1, &tb);
	glBindTexture(GL_TEXTURE_2D, tb);


	glTexImage2D(GL_TEXTURE_2D,
		0, static_cast<GLint>(GL_RGBA), g->bitmap.width, g->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, g->bitmap.buffer);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
	GLuint texunif = glGetUniformLocation(progid, "samp");

	glUniform1i(texunif, static_cast<GLint>(GL_TEXTURE0));
	glActiveTexture(GL_TEXTURE0);*/
	render_text("Hello!", -0.9, 0, 100);
	//glUseProgram(progid);

	while (!wnd.shouldClose())
	{
		glClear(GL_COLOR_BUFFER_BIT);

		for (int i = 0;i <= 5;i++) {

			glBindBuffer(GL_ARRAY_BUFFER, i*2 + 1);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, i*2 + 2);
			GLuint texunif = glGetUniformLocation(progid_shader, "samp");

			glBindTexture(GL_TEXTURE_2D, i+1);
			glUniform1i(texunif, static_cast<GLint>(GL_TEXTURE0 + i));
			glActiveTexture(GL_TEXTURE0 + i);

			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0,
				4,
				GL_FLOAT,
				GL_FALSE,
				8 * sizeof(float),
				NULL);
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1,
				4,
				GL_FLOAT,
				GL_FALSE,
				8 * sizeof(float),
				(const void*)(4 * sizeof(float)));

			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		}

		
		wnd.update();
	}
	Logger::println("Terminating");
}