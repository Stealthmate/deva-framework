#include "Deva.hpp"

#include "System/DevaLogger.hpp"
namespace 
{
	using namespace DevaFramework;
	
	int __deva_init_util()
	{
		DevaLogger::log.println("Initializing Util...");
		return DevaFramework::DEVA_INIT_UTIL();
	}

	int __deva_init_math()
	{
		DevaLogger::log.println("Initializing Math...");
		return DevaFramework::DEVA_INIT_MATH();
	}

	int __deva_init_graphics()
	{
		DevaLogger::log.println("Initializing Graphics...");
		return DevaFramework::DEVA_INIT_GRAPHICS();
	}
	int __deva_init_window()
	{
		DevaLogger::log.println("Initializing Window...");

		int success = DevaFramework::DEVA_INIT_WINDOW();

		switch (success) {
		case 1:
		{
			DevaLogger::log.err.println("Could not load GLFW.");
		} break;
		}
		return DevaFramework::DEVA_INIT_WINDOW();
	}
}


int DevaFramework::DEVA_INIT()
{

	DevaLogger::log << "Initializing Deva..." << Logger::endl;
	if (__deva_init_util() != 0) return 1;
	if (__deva_init_math() != 0) return 2;
	if (__deva_init_graphics() != 0) return 3;
	if (__deva_init_window() != 0) return 4;
	return 0;
}