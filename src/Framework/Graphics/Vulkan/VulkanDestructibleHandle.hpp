#ifndef DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_DESTRUCTIBLE_HANDLE_HPP
#define DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_DESTRUCTIBLE_HANDLE_HPP

#include "Config.hpp"
#include "VulkanDevice.hpp"

#include <memory>
#include <functional>

namespace DevaFramework {
	template<typename T, class Parent>
	class VulkanDestructibleHandle {

		typedef void(*InstanceLocalDeleter)(VkInstance, T, VkAllocationCallbacks);
		typedef void(*DeviceLocalDeleter)(VkDevice, T, VkAllocationCallbacks);
		

		T mHandle;
		std::weak_ptr<Parent> parent;
		std::function<void(Parent, T)> deleter;

		VulkanDestructibleHandle(std::weak_ptr<Parent> parent, InstanceLocalDeleter deleter) {
			this->parent = parent;
			this->mHandle = VK_NULL_HANDLE;
			this->deleter = [parent, deleter](T mHandle) {
				if (!parent.expired() && mHandle != VK_NULL_HANDLE) {
					deleter(parent->mHandle(), );
				}
			};
		}

		~VulkanDestructibleHandle() {
			
		}
	};
}

#endif // DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_DESTRUCTIBLE_HANDLE_HPP