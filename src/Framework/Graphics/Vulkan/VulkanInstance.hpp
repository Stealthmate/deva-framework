#ifndef DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_INSTANCE
#define DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_INSTANCE

#include "Config.hpp"
#include "VulkanPhysicalDevice.hpp"
#include "VulkanInstanceFunctionSet.hpp"

namespace DevaFramework
{
	struct VulkanInstance {
		VkInstance handle;
		VulkanInstanceFunctionSet vk;
		std::vector<VulkanPhysicalDevice> physicalDevices;
	};

	namespace Vulkan {

		DEVA_FRAMEWORK_API VulkanInstance createInstanceDefault();
		DEVA_FRAMEWORK_API VulkanInstance createInstance(const VkInstanceCreateInfo &info);

		DEVA_FRAMEWORK_API void destroyObject(VulkanInstance &instance);

		template<typename T>
		void destroyObject(const VulkanInstance &instance, T& obj) {
			static_assert("No overload found for type");
		}
	}
}



#endif //DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_INSTANCE
