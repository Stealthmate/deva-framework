#ifndef DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_OBJECT_HPP
#define DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_OBJECT_HPP

#include "Config.hpp"
#include <functional>
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
			swap(temp);
			return *this;
		}
		~VulkanObject() = default;

		void swap(VulkanObject& rhs) {
			using std::swap;
			swap(mHandle, rhs.mHandle);
			swap(mInfo, rhs.mInfo);
		}

		const ObjectInfo& info() const noexcept {
			return mInfo;
		}
		
		ObjectType handle() const noexcept {
			return mHandle;
		}

		void reset() {
			mHandle = VK_NULL_HANDLE;
			mInfo = ObjectInfo();
		}

	protected:
		ObjectType mHandle;
		ObjectInfo mInfo;
	};

	template<typename OT, typename OI>
	void swap(VulkanObject<OT, OI> &lhs, VulkanObject<OT, OI> &rhs) {
		lhs.swap(rhs);
	}
}

#endif //DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_OBJECT_HPP