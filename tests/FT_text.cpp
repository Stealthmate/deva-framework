#include <iostream>

#include <glbinding/gl/gl.h>
#include <glbinding/Binding.h>

#define DEVA_USING_GRAPHICS
#define DEVA_USING_WINDOW
#define DEVA_USING_UTIL
#include "../src/Deva.hpp"

using namespace DevaFramework;
using namespace gl;
using namespace glbinding;

void OnKey(Window &win, Key k, InputAction ia, int modmask)
{
	if (k == Key::KEY_ESCAPE) win.close();
}

#include <ft2build.h>
#include FT_FREETYPE_H

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

	const float triangle_coords_colors[] =
	{ -1.0f, -1.0f, +0.0f, +1.0f,
		+1.0f, -1.0f, +0.0f, +1.0f,
		+1.0f, +1.0f, +0.0f, +1.0f,
		+1.0f, +1.0f, +0.0f, +1.0f,
		-1.0f, +1.0f, +0.0f, +1.0f,
		-1.0f, -1.0f, +0.0f, +1.0f };

	GLuint buffer = 0;

	glUseProgram(progid);
	glGenBuffers(1, &buffer);
	glBindBuffer(gl::GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(float), &triangle_coords_colors[0], GL_STATIC_DRAW);

	GLuint mvp_unif = glGetUniformLocation(progid, "MVP");
	Image img = Image::loadImageFromFile("SS1.png", ImageFormat::PNG);
	GLuint tb;
	glGenTextures(1, &tb);
	glBindTexture(GL_TEXTURE_2D, tb);

	FT_Library ft;

	if (FT_Init_FreeType(&ft)) {
		fprintf(stderr, "Could not init freetype library\n");
		return -1;
	}

	FT_Face face;

	if (FT_New_Face(ft, "testfont.ttf", 0, &face)) {
		fprintf(stderr, "Could not open font\n");
		return -1;
	}

	FT_Set_Pixel_Sizes(face, 0, wnd.getHeight());

	if (FT_Load_Char(face, 'X', FT_LOAD_RENDER)) {
		fprintf(stderr, "Could not load character 'X'\n");
		return -1;
	}
	Logger::println("What");
	FT_GlyphSlot g = face->glyph;

	glTexImage2D(GL_TEXTURE_2D,
		0, static_cast<GLint>(GL_RGBA), g->bitmap.width, g->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, g->bitmap.buffer);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
	GLuint texunif = glGetUniformLocation(progid, "samp");

	glUniform1i(texunif, static_cast<GLint>(GL_TEXTURE0));
	glActiveTexture(GL_TEXTURE0);
	glUseProgram(progid);


	while (!wnd.shouldClose())
	{
		glClear(GL_COLOR_BUFFER_BIT);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0,
			4,
			GL_FLOAT,
			GL_FALSE,
			0,
			NULL);

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1,
			4,
			GL_FLOAT,
			GL_FALSE,
			0,
			NULL);

		glDrawArrays(GL_TRIANGLES, 0, 12);

		wnd.update();
	}
	Logger::println("Terminating");
}
