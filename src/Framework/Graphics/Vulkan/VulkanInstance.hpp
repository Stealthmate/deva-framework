#ifndef DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_INSTANCE
#define DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_INSTANCE

#include "Config.hpp"
#include "VulkanObject.hpp"
#include "VulkanPhysicalDevice.hpp"
#include "InstanceFunctionSet.hpp"

namespace DevaFramework
{
	struct VulkanInstanceInfo {
		std::vector<VulkanPhysicalDeviceTraits> physicalDevices;
	};

	class VulkanInstance : public VulkanObject<VkInstance, VulkanInstanceInfo> {
	public:
		DEVA_FRAMEWORK_API static VulkanInstance createDefault();
		DEVA_FRAMEWORK_API static VulkanInstance create(const VkInstanceCreateInfo &info);

		DEVA_FRAMEWORK_API VulkanInstance() noexcept;
		DEVA_FRAMEWORK_API VulkanInstance(VulkanInstance &&vkinstance) noexcept;
		DEVA_FRAMEWORK_API VulkanInstance& operator=(VulkanInstance &&vkinstance) noexcept;
		DEVA_FRAMEWORK_API void swap(VulkanInstance &rhs);

		DEVA_FRAMEWORK_API const VulkanInstanceFunctionSet& vk() const noexcept { return mVk; }

	private:
		VulkanInstanceFunctionSet mVk;

		VulkanInstance(VkInstance handle); //Wraps the mHandle
		VulkanInstance(const VkInstanceCreateInfo &info);
	};

	DEVA_FRAMEWORK_API void swap(VulkanInstance &lhs, VulkanInstance &rhs);

	namespace Vulkan {

		DEVA_FRAMEWORK_API void destroyObject(VulkanInstance &instance);

		template<typename T>
		void destroyObject(const VulkanInstance &instance, T& obj) {
			static_assert("No overload found for type");
		}
	}
}



#endif //DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_INSTANCE
