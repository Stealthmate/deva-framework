#ifndef DEVA_FRAMEWORK_GRAPHICS_VULKAN_BUFFER
#define DEVA_FRAMEWORK_GRAPHICS_VULKAN_BUFFER

#include "Config.hpp"

namespace DevaFramework {
	namespace Vulkan {
		class Buffer {
			VkBuffer handle;
			void* memory;

		public:

			DEVA_FRAMEWORK_API Buffer();
		};
	}
}

#endif //DEVA_FRAMEWORK_GRAPHICS_VULKAN_BUFFER