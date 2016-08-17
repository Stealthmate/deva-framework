#ifndef DEVA_ENGINE_RENDERER_HPP
#define DEVA_ENGINE_RENDERER_HPP

#include "Config.hpp"

namespace DevaEngine
{
	class Renderer
	{
	public:
		Renderer();
		~Renderer();

		//private:
		void _InitInstance();
		void _DeInitInstance();

		void _InitDevice();
		void _DeInitDevice();

		void _SetupDebug();
		void _InitDebug();
		void _DeInitDebug();

		VkInstance					_instance = nullptr;
		VkPhysicalDevice			_gpu = nullptr;
		VkDevice					_device = nullptr;
		VkPhysicalDeviceProperties	_gpu_properties = {};

		uint32_t					_graphics_family_index = 0;

		std::vector<const char*>	_instance_layers;
		std::vector<const char*>	_instance_extensions;
		//	std::vector<const char*>	_device_layers;				// depricated
		std::vector<const char*>	_device_extensions;

		VkDebugReportCallbackEXT	_debug_report = nullptr;
		VkDebugReportCallbackCreateInfoEXT		debug_callback_create_info = {};
	};
}

#endif //DEVA_ENGINE_REDNERER_HPP