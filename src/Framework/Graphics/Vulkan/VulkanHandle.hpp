#ifndef DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_HANDLE_HPP
#define DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_HANDLE_HPP

#include "Config.hpp"

#include "VulkanInstance.hpp"
#include "VulkanDevice.hpp"

#include <functional>

namespace DevaFramework {

	template<typename HandleType>
	class VulkanHandle {
	public:
		VulkanHandle() : mHandle(VK_NULL_HANDLE) {
			deleter = [](HandleType handle) {
				LOG.w(strformat("No deleter specified for handle {} = {}", typeid(HandleType).name(), strm(handle)));
			};
		}
		VulkanHandle(VkInstance instance, std::function<void(VkInstance, HandleType, VkAllocationCallbacks*)> deletef) : VulkanHandle()
		{
			this->deleter = [instance, deletef](HandleType obj) {
				deletef(instance, obj, nullptr);
			};
		}

		VulkanHandle(VkDevice device, std::function<void(VkDevice, HandleType, VkAllocationCallbacks*)> deletef) : VulkanHandle()
		{
			this->deleter = [device, deletef](HandleType obj) {
				deletef(device, obj, nullptr);
			};
		}

		VulkanHandle(const VulkanHandle<HandleType> &vd) = delete;
		VulkanHandle(VulkanHandle<HandleType> &&vd) : VulkanHandle()
		{
			mHandle = vd.mHandle;
			deleter = vd.deleter;
			vd.mHandle = VK_NULL_HANDLE;
			vd.deleter = [](HandleType) {};
		}

		VulkanHandle<HandleType>& operator=(const VulkanHandle<HandleType> &vd) = delete;
		VulkanHandle<HandleType>& operator=(VulkanHandle<HandleType> &&vd)
		{
			if (mHandle != vd.mHandle)
			{
				cleanup();
				mHandle = vd.mHandle;
				deleter = vd.deleter;
				vd.mHandle = VK_NULL_HANDLE;
				vd.deleter = [](HandleType) {};
			}

			return *this;
		}

		operator HandleType() const {
			return mHandle;
		}

		bool operator==(const VulkanHandle<HandleType> &rhs) {
			return mHandle == rhs.handle;
		}
		
		bool operator!=(const VulkanHandle<HandleType> &rhs) {
			return !this->operator==(rhs);
		}

		virtual ~VulkanHandle()
		{
			cleanup();
		}

		HandleType * replace() {
			cleanup();
			return &mHandle;
		}

		void replace(HandleType newHandle) {
			cleanup();
			mHandle = newHandle;
		}

		HandleType handle() {
			return mHandle;
		}

	private:

		HandleType mHandle;
		std::function<void(HandleType)> deleter;

		void cleanup()
		{
			if (mHandle != VK_NULL_HANDLE) {
				LOG.d(strformat("Destroy handle {} = {}", typeid(HandleType).name(), strm(mHandle)));
				deleter(mHandle);
			}
			mHandle = VK_NULL_HANDLE;
		}

	};
}


#endif //DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_HANDLE_HPP