#include <iostream>

#include <glbinding/gl/gl.h>
#include <glbinding/Binding.h>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "../src/Window/Window.hpp"
#include "../src/Graphics/Common.hpp"
#include "../src/Util/Common.hpp"
#include "../src/System/Logger.hpp"
#include "../src/Graphics/Image.hpp"


int main()
{
	using namespace DevaFramework;
	using namespace gl;
	using namespace glbinding;

	Window &wnd = Window::createWindow(800, 600, "Test_OpenGL");
	Window::setCurrentWindow(wnd);

	Logger::log("Created Window");

	glbinding::Binding::initialize();

	Logger::log("Initialized glBinding");

	std::string vshader = readTextFile("shaders/Image.vertex.glsl");
	std::string fshader = readTextFile("shaders/Image.fragment.glsl");

	GLuint progid = loadShaderSet(vshader, fshader);

	Logger::log("Loaded shaders");

	const float triangle_coords_colors[] =
	{  -1.f, -1.f, 0.f, 1.f,
		1.f, -1.f, 0.f, 1.f,
		1.f, 1.f, 0.f, 1.f,
		1.f, 1.f, 0.f, 1.f ,
	    -1.f, 1.f, 0.f, 1.f,
	    -1.f, -1.f, 0.f, 1.f};

	const char img_data[] = {
		20, 0, 20,
		0, 20, 20,
		20, 0, 20,
		20, 20, 0,
		20, 0, 0,
		0, 20, 0,
		0, 0, 20,
		20, 0, 20,
		20, 20, 0,
		20, 0, 20,
		0, 20, 20,
		20, 0, 20,
		20, 20, 0,
		20, 0, 0,
	};
	const unsigned char img_data_1[] = {
		50, 0, 0,
		50, 0, 0,
		50, 0, 0,
		50, 0, 0,
		50, 0, 0,
		50, 0, 0,
		0, 0, 0,
		0, 0, 0,
		0, 0, 0,
		0, 0, 0,
		0, 0, 0,
		0, 0, 0,
		0, 0, 0,
		0, 0, 0,
		0, 0, 0,
		0, 0, 0,
	};

	GLuint buffer = 0;

	glUseProgram(progid);
	glGenBuffers(1, &buffer);
	glBindBuffer(gl::GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(float), &triangle_coords_colors[0], GL_STATIC_DRAW);

	Logger::log("Loaded buffer");

	GLuint mvp_unif = glGetUniformLocation(progid, "MVP");
	Image img = Image::loadImageFromFile("SS10.png", ImageFormat::PNG);
	GLuint tb;
	glGenTextures(1, &tb);
	glBindTexture(GL_TEXTURE_2D, tb);
	glTexImage2D(GL_TEXTURE_2D,
		0, static_cast<GLint>(GL_RGBA), img.width, img.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, img.getData());
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
	Logger::log("Terminating");
}
