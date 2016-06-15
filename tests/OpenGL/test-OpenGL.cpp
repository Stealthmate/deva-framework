#include "../../src/Deva.hpp"

#include <glbinding/gl/gl.h>
#include <glbinding/Binding.h>

namespace
{
	const char* TEST_DESCRIPTION =
		R"description(Test Description:
	This test should open a window and draw a triangle on it. The triangle should take the maximum available space
	and it's bottom two corners should be at the bottom two corners of the window. The triangle should also be colored - 
	bottom left should be colored green; bottom right should be colored red; top should be colored blue. The window
	should close when Escape is pressed.)description";


#include "VertexShader.inl"
#include "FragmentShader.inl"

	using namespace DevaFramework;
	using namespace gl;
	using namespace glbinding;

	void OnKey(Window &win, Key k, InputAction ia, int modmask)
	{
		if (k == Key::KEY_ESCAPE) win.close();
	}

	std::vector<float> vertex_data =
	{ -1.f, -1.f, 0.f, 1.f, //XYZW
		0.f,  1.f, 0.f, 1.f, //RGBA
		1.f, -1.f, 0.f, 1.f, //XYZW
		1.f,  0.f, 0.f, 1.f, //RGBA
		0.f,  1.f, 0.f, 1.f, //XYZW
		0.f,  0.f, 1.f, 1.f }; //RGBA

	VBO test_vbo = VBO(
		std::vector<char>(reinterpret_cast<char*>(&vertex_data[0]), reinterpret_cast<char*>(&vertex_data[0] + vertex_data.size())),
		3,
		(GLuint) vertex_data.size(),
		(GLuint) vertex_data.size() * sizeof(float),
		{
			VAO(
				0,
				4,
				GL_FLOAT,
				(GLuint) sizeof(float) * 8,
				0
			),
			VAO(
				1,
				4,
				GL_FLOAT,
				(GLuint) sizeof(float) * 8,
				(uintptr_t) sizeof(float) * 4)
		},
		2
	);



}

int main()
{

	DEVA_INIT();

	DevaLogger::log.println(TEST_DESCRIPTION);
	DevaLogger::log << DevaLogger::NumberFormat::HEX << 255 << Logger::endl;

	Window &wnd = Window::createWindow(800, 600, "test-OpenGL");
	Window::setCurrentWindow(wnd);
	wnd.setOnKeyActionCallback(OnKey);

	glbinding::Binding::initialize();
	DevaLogger::log.println("Initialized glBinding");

	std::string vshader = VERTEX_SHADER;
	std::string fshader = FRAGMENT_SHADER;

	Shader vs = Shader(GL_VERTEX_SHADER, vshader);
	Shader fs = Shader(GL_FRAGMENT_SHADER, fshader);

	ShaderProgram prog = ShaderProgram();
	prog.attachShader(vs).attachShader(fs).link();

	GLuint progid = prog.getHandle();

	DevaLogger::log.println("Loaded Shaders");

	GLuint buffer = 0;

	glUseProgram(progid);
	glGenBuffers(1, &buffer);
	glBindBuffer(gl::GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, test_vbo.data_byteSize, &test_vbo.data[0], GL_STATIC_DRAW);

	DevaLogger::log.println("Loaded buffer");

	for (auto vao : test_vbo.vaos)
	{
		glEnableVertexAttribArray(vao.id);
		glVertexAttribPointer(vao.id,
			vao.nValuesPerVertex,
			vao.dataType,
			GL_FALSE,
			vao.stride,
			(const void*)vao.offset);
	}

	while (!wnd.shouldClose())
	{
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawArrays(GL_TRIANGLES, 0, test_vbo.nVertices);

		wnd.update();
	}

	DevaLogger::log.println("Test successful.");
	DevaLogger::log.println("Terminating");
}