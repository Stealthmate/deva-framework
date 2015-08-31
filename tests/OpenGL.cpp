#include <iostream>

#include <glbinding/gl/gl.h>
#include <glbinding/Binding.h>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "../src/Window/Window.hpp"
#include "../src/Graphics/Common.hpp"
#include "../src/Util/Common.hpp"

#include "../src/Math/Vector.hpp"


int main()
{
	using namespace DevaFramework;
	using namespace gl;
	using namespace glbinding;
	Window &wnd = Window::createWindow(800, 600, "Test_OpenGL");
	Window::setCurrentWindow(wnd);

	glbinding::Binding::initialize();

	std::string vshader = readTextFile("shaders/Empty.vertex.glsl");
	std::string fshader = readTextFile("shaders/Empty.fragment.glsl");

	GLuint progid = loadShaderSet(vshader, fshader);

	const float triangle_coords_colors[] =
	{ -1.f, -1.f, 0.f, 1.f,
	  -1.f,  1.f, 0.f, 1.f,
	   1.f, -1.f, 0.f, 1.f,
 	   1.f,  0.f, 0.f, 1.f,
	   0.f,  1.f, 0.f, 1.f,
	   0.f,  0.f, 1.f, 1.f };

	GLuint buffer = 0;

	glUseProgram(progid);
	glGenBuffers(1, &buffer);
	glBindBuffer(gl::GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(float), &triangle_coords_colors[0], GL_STATIC_DRAW);

	GLuint mvp_unif = glGetUniformLocation(progid, "MVP");

	float ds = 0.01f, dr = 0.05f;
	float scale = 1.0f, rotate = 0;
	glm::mat4 mvp = glm::mat4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
	glm::mat4 mRot;
	glm::mat4 mScale;
	mRot = glm::rotate(glm::mat4(), rotate, glm::vec3(0, 0, 0));
	mScale = glm::scale(glm::mat4(), glm::vec3(scale, scale, 1));

	glm::mat4 model = glm::scale(glm::mat4(), glm::vec3(300.f, 300.f, 1.f));

	glm::mat4 view = glm::translate(glm::vec3(0.f, 0.f, 0.f));
	
	glm::mat4 proj = glm::ortho(-400.f, 400.f, -300.f, 300.f);






	while (!wnd.shouldClose())
	{
		glClear(GL_COLOR_BUFFER_BIT);

		if (scale >= 1.0f || scale <= 0.2f) ds = -ds;
		scale += ds;
		if (rotate + dr == 360) rotate = -dr;
		rotate += dr;

		mRot = glm::rotate(glm::mat4(), rotate, glm::vec3(0, 0, 1));
		mScale = glm::scale(glm::mat4(), glm::vec3(scale, scale, 1));
		mvp = proj * view * model;

		glUniformMatrix4fv(mvp_unif, 1, GL_FALSE, &mvp[0][0]);
		
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
}
