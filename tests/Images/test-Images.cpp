#include <iostream>

#include <glbinding/gl/gl.h>
#include <glbinding/Binding.h>

#include <Deva.hpp>

namespace 
{
	const char* TEST_DESCRIPTION =
		R"description(Test Description:
	This test should open a window and draw a rectangle on it. The rectangle should be textured, 
	with the texture being an image. 
	The window should close when Escape is pressed.)description";

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
	{ 
		-1.0f, -1.0f, +0.0f, +1.0f,
		+1.0f, -1.0f, +0.0f, +1.0f,
		+1.0f, +1.0f, +0.0f, +1.0f,
		+1.0f, +1.0f, +0.0f, +1.0f,
		-1.0f, +1.0f, +0.0f, +1.0f,
		-1.0f, -1.0f, +0.0f, +1.0f 
	};

	VBO test_vbo = VBO(
		std::vector<char>(reinterpret_cast<char*>(&vertex_data[0]), reinterpret_cast<char*>(&vertex_data[0] + vertex_data.size())),
		6,
		(GLuint)vertex_data.size(),
		(GLuint)vertex_data.size() * sizeof(float),
		{
			VAO(
				0,
				4,
				GL_FLOAT,
				0,
				0),
			VAO(
				1,
				4,
				GL_FLOAT,
				0,
				0)
		},
		2
	);

}

int main()
{

	DEVA_INIT();

	DevaLogger::log.println(TEST_DESCRIPTION);

	Window &wnd = Window::createWindow(1366, 768, "OpenGL Display Image");
	Window::setCurrentWindow(wnd);
	wnd.setOnKeyActionCallback(OnKey);

	glbinding::Binding::initialize();

	Shader vertex_shader = Shader(GL_VERTEX_SHADER, VERTEX_SHADER);
	Shader fragment_shader = Shader(GL_FRAGMENT_SHADER, FRAGMENT_SHADER);
	ShaderProgram shadprog;
	shadprog.attachShader(vertex_shader).attachShader(fragment_shader);
	shadprog.link();
	GLuint progid = shadprog.getHandle();

	GLuint buffer = 0;

	glUseProgram(progid);
	glGenBuffers(1, &buffer);
	glBindBuffer(gl::GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, test_vbo.data_byteSize, &test_vbo.data[0], GL_STATIC_DRAW);

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

	Image img = Image::loadImageFromFile("resources/SS1.png", ImageFormat::PNG);
	
	GLuint tb;
	glGenTextures(1, &tb);
	glBindTexture(GL_TEXTURE_2D, tb);
	glTexImage2D(GL_TEXTURE_2D,
		0, static_cast<GLint>(GL_RGBA), img.width, img.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, img.getData());

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);

	setShaderUniform(glGetUniformLocation(progid, "samp"), static_cast<GLint>(GL_TEXTURE0));
	glActiveTexture(GL_TEXTURE0);

	while (!wnd.shouldClose())
	{
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawArrays(GL_TRIANGLES, 0, test_vbo.nVertices);

		wnd.update();
	}

	DevaLogger::log.println("Test Successful");
	DevaLogger::log.println("Terminating");
}