#include "Deva.hpp"

#include "DevaLogger.hpp"
namespace 
{
	using namespace DevaFramework;
}


int DevaFramework::DEVA_INIT(VkInstanceCreateInfo vulkan_info)
{

	DevaLogger::log.println("Initializing Deva Framework...");
	
	int err = 0;

	err = DEVA_INIT_UTIL();
	if (err != 0) return 1;

	err = DEVA_INIT_MATH();
	if (err != 0) return 2;

	err = DEVA_INIT_GRAPHICS(vulkan_info);
	if (err != 0) return 3;

	err = DEVA_INIT_WINDOW();
	if (err != 0) return 4;

	return 0;
}