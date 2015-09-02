#include <iostream>

#include <glbinding/gl/gl.h>
#include <glbinding/Binding.h>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "../src/Window/Window.hpp"
#include "../src/Graphics/Common.hpp"
#include "../src/Util/Common.hpp"
#include "../src/System/Logger.hpp"
#include "../src/Graphics/Shader.hpp"
#include "../src/Graphics/ShaderProgram.hpp"

int main()
{
	using namespace DevaFramework;
	using namespace gl;
	using namespace glbinding;

	Window &wnd = Window::createWindow(800, 600, "Test_OpenGL");
	Window::setCurrentWindow(wnd);

	Logger::log << "Created Window";

	glbinding::Binding::initialize();

	Logger::log << "Initialized glBinding";

	std::string vshader = readTextFile("shaders/Empty.vertex.glsl");
	std::string fshader = readTextFile("shaders/Empty.fragment.glsl");

	Shader vs = Shader(GL_VERTEX_SHADER, vshader);
	Shader fs = Shader(GL_FRAGMENT_SHADER, fshader);

	Logger::log << vs.compile();
	Logger::log << fs.compile();

	ShaderProgram prog = ShaderProgram();
	prog.attachShader(vs).attachShader(fs);

	Logger::log << prog.link();

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

	Logger::log << "Loaded buffer";

	GLuint mvp_unif = glGetUniformLocation(progid, "MVP");

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
	Logger::log << "Terminating";
}
