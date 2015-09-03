#include <iostream>

#include <glbinding/gl/gl.h>
#include <glbinding/Binding.h>

#include "../src/Window/Window.hpp"
#include "../src/Graphics/Common.hpp"
#include "../src/Util/Common.hpp"
#include "../src/System/Logger.hpp"
#include "../src/Graphics/Shader.hpp"
#include "../src/Graphics/ShaderProgram.hpp"

using namespace DevaFramework;
using namespace gl;
using namespace glbinding;

void OnKey(Window &win, Key k, InputAction ia, int modmask)
{
	if (k == Key::KEY_ESCAPE) win.close();
}

int main()
{

	Window &wnd = Window::createWindow(800, 600, "Test_OpenGL");
	Window::setCurrentWindow(wnd);
	wnd.setOnKeyActionCallback(OnKey);

	Logger::println("Created Window");
	glbinding::Binding::initialize();

	Logger::println("Initialized glBinding");

	std::string vshader = readTextFile("shaders/Empty.vertex.glsl");
	std::string fshader = readTextFile("shaders/Empty.fragment.glsl");

	Shader vs = Shader(GL_VERTEX_SHADER, vshader);
	Shader fs = Shader(GL_FRAGMENT_SHADER, fshader);

	ShaderProgram prog = ShaderProgram();
	prog.attachShader(vs).attachShader(fs);

	Logger::println(prog.link());

	GLuint progid = prog.getHandle();

	Logger::log << "Loaded shaders";

	const float triangle_coords_colors[] =
	{ -1.f, -1.f, 0.f, 1.f, //XYZW
	   0.f,  1.f, 0.f, 1.f, //RGBA
	   1.f, -1.f, 0.f, 1.f, //XYZW
 	   1.f,  0.f, 0.f, 1.f, //RGBA
	   0.f,  1.f, 0.f, 1.f, //XYZW
	   0.f,  0.f, 1.f, 1.f }; //RGBA

	GLuint buffer = 0;

	glUseProgram(progid);
	glGenBuffers(1, &buffer);
	glBindBuffer(gl::GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(float), &triangle_coords_colors[0], GL_STATIC_DRAW);

	Logger::println("Loaded buffer");

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
			(void*) 48);

		glDrawArrays(GL_TRIANGLES, 0, 3);

		wnd.update();
	}
	Logger::println("Terminating");
}
