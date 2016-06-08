#ifndef DEVA_FRAMEWORK_MASTER_H
#define DEVA_FRAMEWORK_MASTER_H

#include "Config.hpp"

#include "System/Master.hpp"

#ifdef DEVA_USING_UTIL
#include "Util/Master.hpp"
int __deva_init_util() 
{
	DevaFramework::Logger::println("Initializing Util...");
	return DevaFramework::DEVA_INIT_UTIL();
}
#else
int __deva_init_util() { return 0; }
#endif

#ifdef DEVA_USING_MATH
#include "Math/Master.hpp"
int __deva_init_math() 
{
	DevaFramework::Logger::println("Initializing Math...");
	return DevaFramework::DEVA_INIT_MATH();
}
#else
int __deva_init_math() { return 0; }
#endif

#ifdef DEVA_USING_GRAPHICS
#include "Graphics/Master.hpp"
int __deva_init_graphics() 
{
	DevaFramework::Logger::println("Initializing Graphics...");
	return DevaFramework::DEVA_INIT_GRAPHICS();
}
#else
int __deva_init_graphics() { return 0; }
#endif

#ifdef DEVA_USING_WINDOW
#include "Window/Master.hpp"
int __deva_init_window()
{
	DevaFramework::Logger::println("Initializing Window...");

	int success = DevaFramework::DEVA_INIT_WINDOW();

	switch (success) {
		case 1:
		{
			DevaFramework::Logger::err.println("Could not load GLFW.");
		} break;
	}
	return DevaFramework::DEVA_INIT_WINDOW();
}
#else
int __deva_init_window() { return 0; }
#endif

namespace DevaFramework
{
	int DEVA_INIT() 
	{

		DevaFramework::Logger::println("Initializing Deva...");
		if (__deva_init_util() != 0) return 1;
		if (__deva_init_math() != 0) return 2;
		if (__deva_init_graphics() != 0) return 3;
		if (__deva_init_window() != 0) return 4;
		return 0;
	}
}

#endif //DEVA_FRAMEWORK_MASTER_H