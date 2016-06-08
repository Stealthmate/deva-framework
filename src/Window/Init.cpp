#include "Init.hpp"

#include <GLFW/glfw3.h>

using namespace DevaFramework;

bool DevaFramework::__DEVA_FRAMEWORK_WINDOW_INIT = false;

int DevaFramework::DEVA_INIT_WINDOW() {
	int success = glfwInit();

	if (success != GL_TRUE) return 1;


	__DEVA_FRAMEWORK_WINDOW_INIT = true;
	return 0;
}