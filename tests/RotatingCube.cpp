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
#include "../src/Math/Matrix.hpp"
#include "../src/Math/Matrix_Vector.hpp"
#define _USE_MATH_DEFINES
#include <math.h>

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

	std::string vshader = readTextFile("shaders/Empty.vertex.glsl");
	std::string fshader = readTextFile("shaders/Empty.fragment.glsl");

	GLuint progid = loadShaderSet(vshader, fshader);

	Logger::log("Loaded shaders");

	GLfloat coords[] =
	{
		-0.5f, -0.5f, +0.0f, +1.0f,//x
		+0.0f, +1.0f, +0.0f, +1.0f,//r
		+0.5f, -0.5f, +0.0f, +1.0f,//x
		+1.0f, +0.0f, +0.0f, +1.0f,//r
		+0.5f, +0.5f, +0.0f, +1.0f,//x
		+0.0f, +0.0f, +1.0f, +1.0f,//r
		-0.5f, +0.5f, +0.0f, +1.0f,//x
		+0.0f, +1.0f, +0.0f, +1.0f,//r
		-0.5f, -0.5f, +0.5f, +1.0f,//x
		+1.0f, +0.0f, +0.0f, +1.0f,//r
		+0.5f, -0.5f, +0.5f, +1.0f,//x
		+0.0f, +0.0f, +1.0f, +1.0f,//r
		+0.5f, +0.5f, +0.5f, +1.0f,//x
		+0.0f, +1.0f, +0.0f, +1.0f,//r
		-0.5f, +0.5f, +0.5f, +1.0f,//x
		+1.0f, +0.0f, +0.0f, +1.0f,//r
	};

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

	GLfloat mvp[] =
	{
		+1.0f, +0.0f, +0.0f, +0.0f,
		+0.0f, +1.0f, +0.0f, +0.0f,
		+0.0f, +0.0f, +1.0f, +0.0f,
		+0.0f, +0.0f, +0.0f, +1.0f
	};

	vec4 v = {2, 2, 0, 1};
	//Logger::log(v.to_str());
	mat4 m = { vec4{2, 0, 0, 0}, vec4{0, 3, 0, 0}, vec4{0, 0, 1, 0}, vec4{0, 0, 0, 1} };
	//Logger::log(m.to_str());
	Logger::log((m*v).to_str());
	GLfloat Near_plane = 0.1f;
	GLfloat Far_plane = 1000.f;
	GLfloat frustum_length = Far_plane - Near_plane;
	GLfloat FoV = 70.f * M_PI / 180.f;
	GLfloat aspect_ratio = 800.f / 600.f;
	GLfloat y_scale = (1/tan(FoV)) * aspect_ratio;
	GLfloat x_scale = y_scale / aspect_ratio;
	GLfloat projection_matrix[] = 
	{
		x_scale, 0, 0, 0,
		0, y_scale, 0, 0,
		0, 0, -(Far_plane + Near_plane)/frustum_length, -1,
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
			angle = 1.f;
		}
		angle += dAngle;

		mvp[8] =  sin(angle*M_PI / 180.f);
		mvp[0] =  cos(angle*M_PI / 180.f);
		mvp[2] = -sin(angle*M_PI / 180.f);
		mvp[10] =  cos(angle*M_PI / 180.f);
		glUniformMatrix4fv(mvpunif, 1, GL_FALSE, mvp);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, 0);

		wnd.update();
	}
	Logger::log("Terminating");
}
