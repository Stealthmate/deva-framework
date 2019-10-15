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
		VulkanHandle() noexcept : mHandle(VK_NULL_HANDLE) {
			deleter = [](HandleType handle) {
				LOG.w(strformat("No deleter specified for handle {} = {}", typeid(HandleType).name(), strf(handle)));
			};
		}
		VulkanHandle(
			VkInstance instance, 
			std::function<void(VkInstance, HandleType, VkAllocationCallbacks*)> deletef, 
			HandleType handle = VK_NULL_HANDLE) noexcept 
			: mHandle(handle)
		{
			this->deleter = [instance, deletef](HandleType obj) {
				deletef(instance, obj, nullptr);
			};
		}

		VulkanHandle(
			VkDevice device, 
			std::function<void(VkDevice, HandleType, VkAllocationCallbacks*)> deletef,
			HandleType handle = VK_NULL_HANDLE) noexcept
			: mHandle(handle)
		{
			this->deleter = [device, deletef](HandleType obj) {
				deletef(device, obj, nullptr);
			};
		}

		VulkanHandle(VulkanHandle<HandleType> &&vd) noexcept : VulkanHandle()
		{
			mHandle = vd.mHandle;
			deleter = vd.deleter;
			vd.invalidate();
		}

		VulkanHandle<HandleType>& operator=(VulkanHandle<HandleType> &&vd) noexcept
		{
			if (mHandle != vd.mHandle)
			{
				cleanup();
				mHandle = vd.mHandle;
				deleter = vd.deleter;
				vd.invalidate();
			}

			return *this;
		}

		operator HandleType() const noexcept {
			return mHandle;
		}

		bool operator==(const VulkanHandle<HandleType> &rhs) const noexcept {
			return mHandle == rhs.handle;
		}

		bool operator!=(const VulkanHandle<HandleType> &rhs) const noexcept {
			return !this->operator==(rhs);
		}

		
		~VulkanHandle()
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

		HandleType handle() const noexcept {
			return mHandle;
		}

		void invalidate() {
			mHandle = VK_NULL_HANDLE;
			deleter = [](HandleType) {};
		}

	private:

		HandleType mHandle;
		std::function<void(HandleType)> deleter;

		VulkanHandle(const VulkanHandle<HandleType> &vd) = delete;
		VulkanHandle<HandleType>& operator=(const VulkanHandle<HandleType> &vd) = delete;

		void cleanup()
		{
			if (mHandle != VK_NULL_HANDLE) {
				deleter(mHandle);
			}
			mHandle = VK_NULL_HANDLE;
		}

	};
}


#endif //DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_HANDLE_HPP