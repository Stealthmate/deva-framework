#include <iostream>

#include <glbinding/gl/gl.h>
#include <glbinding/Binding.h>
#include <iostream>

#include "../../src/Deva.hpp"

#define _USE_MATH_DEFINES
#include <math.h>

namespace {

	using namespace DevaFramework;
	using namespace gl;
	using namespace glbinding;

	void OnKey(Window &win, Key k, InputAction ia, int modmask)
	{
		if (k == Key::KEY_ESCAPE) win.close();
	}
}

int main()
{

	DEVA_INIT();

	Window &wnd = Window::createWindow(800, 600, "Test_OpenGL");

	Window::setCurrentWindow(wnd);
	wnd.setOnKeyActionCallback(OnKey);

	DevaLogger::log.println("Created Window");

	glbinding::Binding::initialize();

	DevaLogger::log.println("Initialized glBinding");

	std::string vshader = readTextFile("shaders/Empty.vertex.glsl");
	std::string fshader = readTextFile("shaders/Empty.fragment.glsl");

	GLuint progid = loadShaderSet(vshader, fshader);

	DevaLogger::log.println("Loaded Shaders");

	std::vector<GLfloat> coords =
	{
		+0.00f, +0.00f, -0.05f, +1.00f,
		+1.00f, +1.00f, +0.00f, +1.00f,
		+0.00f, +0.20f, +0.00f, +1.00f,
		+1.00f, +0.00f, +0.00f, +1.00f,
		-0.05f, +0.05f, +0.00f, +1.00f,
		+1.00f, +0.00f, +0.00f, +1.00f,
		-0.20f, +0.05f, +0.00f, +1.00f,
		+1.00f, +0.00f, +0.00f, +1.00f,
		-0.07f, -0.05f, +0.00f, +1.00f,
		+1.00f, +0.00f, +0.00f, +1.00f,
		-0.13f, -0.20f, +0.00f, +1.00f,
		+1.00f, +0.00f, +0.00f, +1.00f,
		+0.00f, -0.10f, +0.00f, +1.00f,
		+1.00f, +0.00f, +0.00f, +1.00f,
		+0.13f, -0.20f, +0.00f, +1.00f,
		+1.00f, +0.00f, +0.00f, +1.00f,
		+0.07f, -0.05f, +0.00f, +1.00f,
		+1.00f, +0.00f, +0.00f, +1.00f,
		+0.20f, +0.05f, +0.00f, +1.00f,
		+1.00f, +0.00f, +0.00f, +1.00f,
		+0.05f, +0.05f, +0.00f, +1.00f,
		+1.00f, +0.00f, +0.00f, +1.00f,
		+0.00f, +0.00f, +0.05f, +1.00f,
		+1.00f, +1.00f, +0.00f, +1.00f,
	};

	std::vector<char> indices =
	{
		0, 1, 2,
		0, 2, 3,
		0, 3, 4,
		0, 4, 5,
		0, 5, 6,
		0, 6, 7,
		0, 7, 8,
		0, 8, 9,
		0, 9, 10,
		0, 10, 1,
		11, 1, 10,
		11, 2, 1,
		11, 3, 2,
		11, 4, 3,
		11, 5, 4,
		11, 6, 5,
		11, 7, 6,
		11, 8, 7,
		11, 9, 8,
		11, 10, 9
	};

	VBO vbo;
	vbo.data = std::vector<char>(reinterpret_cast<char*>(&coords[0]), reinterpret_cast<char*>(&coords[0]) + coords.size() * 4);
	vbo.data_byteSize = coords.size() * 4;
	vbo.data_nValues = 96;
	vbo.nVertices = 12;
	vbo.vaos_size = 2;
	VAO vao1;
	vao1.dataType = GL_FLOAT;
	vao1.id = 0;
	vao1.nValuesPerVertex = 4;
	vao1.offset = 0;
	vao1.stride = 32;
	vbo.vaos.push_back(vao1);
	VAO vao2;
	vao2.dataType = GL_FLOAT;
	vao2.id = 2;
	vao2.nValuesPerVertex = 4;
	vao2.offset = 16;
	vao2.stride = 32;
	vbo.vaos.push_back(vao2);

	Model model = Model(vbo, gl::GL_UNSIGNED_BYTE, indices);

	std::ofstream file_out;
	file_out.open("test.devaobj", std::ofstream::trunc | std::ofstream::binary);
	auto bin = Model::exportBinary(model);

	file_out.write(&bin[0], bin.size());
	file_out.close();

	DevaLogger::log.println("Test");
	try
	{
		model = Model::fromFile("test.devaobj");
	}
	catch (DevaException ex)
	{
		DevaLogger::log.println(ex.what());
	}

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	GLuint vbuf, ibuf;
	glGenBuffers(1, &vbuf);
	glGenBuffers(1, &ibuf);

	glBindBuffer(GL_ARRAY_BUFFER, vbuf);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibuf);
	glBufferData(GL_ARRAY_BUFFER, model.getVBO().data_byteSize, &model.getVBO().data[0], GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.getIndexArray().size(), &model.getIndexArray()[0], GL_STATIC_DRAW);
	glUseProgram(progid);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0,
		model.getVBO().vaos[0].nValuesPerVertex,
		model.getVBO().vaos[0].dataType,
		GL_FALSE,
		model.getVBO().vaos[0].stride,
		0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1,
		model.getVBO().vaos[1].nValuesPerVertex,
		model.getVBO().vaos[1].dataType,
		GL_FALSE,
		model.getVBO().vaos[1].stride,
		reinterpret_cast<const void*>(model.getVBO().vaos[1].offset));

	float angle = 0;

	mat4 mvp =
	{
		vec4{ +1.0f, +0.0f, +0.0f, +0.0f },
		vec4{ +0.0f, +1.0f, +0.0f, +0.0f },
		vec4{ +0.0f, +0.0f, +1.0f, +0.0f },
		vec4{ +0.0f, +0.0f, +0.0f, +1.0f }
	};
	GLfloat Near_plane = 0.1f;
	GLfloat Far_plane = 10.f;
	GLfloat frustum_length = Far_plane - Near_plane;
	GLfloat FoV = 30.f * M_PI / 180.f;
	GLfloat aspect_ratio = 800.f / 600.f;
	GLfloat y_scale = (1 / tan(FoV)) * aspect_ratio;
	GLfloat x_scale = y_scale / aspect_ratio;
	GLfloat projection_matrix[] =
	{
		x_scale, 0, 0, 0,
		0, y_scale, 0, 0,
		0, 0, -(Far_plane + Near_plane) / frustum_length, -1,
		0, 0, -(2 * Far_plane*Near_plane) / frustum_length, 0
	};

	GLuint uniform_PROJ_MAT = glGetUniformLocation(progid, "PROJ_MAT");
	glUniformMatrix4fv(uniform_PROJ_MAT, 1, GL_FALSE, projection_matrix);



	GLuint mvpunif = glGetUniformLocation(progid, "MVP");
	glUniformMatrix4fv(mvpunif, 1, GL_FALSE, mvp);
	float dAngle = rad(1.0f);
	while (!wnd.shouldClose())
	{
		if (angle > TWOPI)
		{
			angle = 0.0f;
		}
		angle += dAngle;

		mvp = roll(angle) * pitch(angle) * yaw(angle);
		glUniformMatrix4fv(mvpunif, 1, GL_FALSE, mvp);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//glDisable(GL_CULL_FACE);
		glDrawElements(GL_TRIANGLES, model.getIndexArray().size(), model.getIndexType(), 0);


		wnd.update();
	}
	DevaLogger::log.println("Terminating");
}