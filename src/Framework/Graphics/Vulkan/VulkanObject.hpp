#ifndef DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_OBJECT_HPP
#define DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_OBJECT_HPP

#include "Config.hpp"

namespace DevaFramework {

	template<typename ObjectType, typename ObjectInfo>
	class VulkanObject {
	public:
		VulkanObject() noexcept : mHandle(VK_NULL_HANDLE) {}

		VulkanObject(ObjectType handle, const ObjectInfo &info) noexcept : mHandle(handle), mInfo(info) {}

		VulkanObject(VulkanObject &&obj) noexcept : mHandle(obj.mHandle), mInfo(obj.mInfo) {
			obj.mHandle = VK_NULL_HANDLE;
			obj.mInfo = ObjectInfo();
		}
		VulkanObject& operator=(VulkanObject &&obj) noexcept {
			VulkanObject temp(std::move(obj));
			std::swap(temp, *this);
			return *this;
		}
		~VulkanObject() = default;

		const ObjectInfo& info() const noexcept {
			return mInfo;
		}
		
		ObjectType handle() const noexcept {
			return mHandle;
		}

	private:
		ObjectType mHandle;
		ObjectInfo mInfo;
	};
}

#endif //DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_OBJECT_HPP