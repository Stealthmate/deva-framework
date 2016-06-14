#include <iostream>

#include <glbinding/gl/gl.h>
#include <glbinding/Binding.h>
#include <iostream>

#define DEVA_USING_WINDOW
#define DEVA_USING_GRAPHICS
#define DEVA_USING_UTIL
#define DEVA_USING_MATH
#include "../src/Deva.hpp"

#define _USE_MATH_DEFINES
#include <math.h>

using namespace DevaFramework;
using namespace gl;
using namespace glbinding;

void OnKey(Window &win, Key k, InputAction ia, int modmask)
{
	if (k == Key::KEY_ESCAPE) win.close();
}

int main()
{

	DEVA_INIT();

	Window &wnd = Window::createWindow(800, 600, "Test_OpenGL");

	Window::setCurrentWindow(wnd);
	wnd.setOnKeyActionCallback(OnKey);

	Logger::println("Created Window");

	glbinding::Binding::initialize();

	Logger::println("Initialized glBinding");

	std::string vshader = readTextFile("shaders/Empty.vertex.glsl");
	std::string fshader = readTextFile("shaders/Empty.fragment.glsl");

	GLuint progid = loadShaderSet(vshader, fshader);

	Logger::println("Loaded Shaders");

	GLfloat coords[] =
	{
		-0.5f, -0.5f, +0.0f, +1.0f,//x
		+0.0f, +1.0f, +0.0f, +1.0f,//r
		+0.5f, -0.5f, +0.0f, +1.0f,//x
		+1.0f, +1.0f, +0.0f, +1.0f,//r
		+0.5f, +0.5f, +0.0f, +1.0f,//x
		+0.0f, +1.0f, +1.0f, +1.0f,//r
		-0.5f, +0.5f, +0.0f, +1.0f,//x
		+1.0f, +1.0f, +0.0f, +1.0f,//r
		-0.5f, -0.5f, +0.5f, +1.0f,//x
		+0.0f, +1.0f, +1.0f, +1.0f,//r
		+0.5f, -0.5f, +0.5f, +1.0f,//x
		+1.0f, +0.0f, +1.0f, +1.0f,//r
		+0.5f, +0.5f, +0.5f, +1.0f,//x
		+0.0f, +1.0f, +1.0f, +1.0f,//r
		-0.5f, +0.5f, +0.5f, +1.0f,//x
		+1.0f, +0.0f, +1.0f, +1.0f,//r
	};
	glFrontFace(GL_CW);
	GLushort indecies[] =
	{
		0,1,2,
		0,2,3,
		0,3,4,
		4,3,7,
		4,7,5,
		5,7,6,
		1,5,6,
		1,6,2,
		2,6,3,
		6,7,3,
		0,4,1,
		1,4,5,
	};

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	GLuint vbuf, ibuf;
	glGenBuffers(1, &vbuf);
	glGenBuffers(1, &ibuf);

	glBindBuffer(GL_ARRAY_BUFFER, vbuf);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibuf);
	glBufferData(GL_ARRAY_BUFFER, sizeof(coords), coords, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indecies), indecies, GL_STATIC_DRAW);
	glUseProgram(progid);

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

	float angle = 0;

	mat4 mvp =
	{
		vec4{ +1.0f, +0.0f, +0.0f, +0.0f },
		vec4{ +0.0f, +1.0f, +0.0f, +0.0f },
		vec4{ +0.0f, +0.0f, +1.0f, +0.0f },
		vec4{ +0.0f, +0.0f, +0.0f, +1.0f }
	};
	GLfloat Near_plane = 0.1f;
	GLfloat Far_plane = 1000.f;
	GLfloat frustum_length = Far_plane - Near_plane;
	GLfloat FoV = 70.f * M_PI / 180.f;
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
	glUniformMatrix4fv(mvpunif, sizeof(mvp), GL_FALSE, mvp);
	float dAngle = 1.0f;
	while (!wnd.shouldClose())
	{
		if (angle > 359)
		{
			angle = 1.0f;
		}
		angle += dAngle;

		mvp = rotate(angle*M_PI / 180.f, vec3{ 0, 1, 0 });
		glUniformMatrix4fv(mvpunif, 1, GL_FALSE, mvp);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, 0);

		wnd.update();
		///TODO: IMplement OBJ file support
	}
	Logger::println("Terminating");
}
