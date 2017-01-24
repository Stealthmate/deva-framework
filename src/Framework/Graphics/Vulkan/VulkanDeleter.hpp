#ifndef DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_DELETER_HPP
#define DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_DELETER_HPP

#include "Config.hpp"

#include "VulkanInstance.hpp"
#include "VulkanDevice.hpp"

#include<functional>

namespace DevaFramework {

	template<typename T>
	class VulkanDeleter {

		T object{ VK_NULL_HANDLE };
		std::function<void(T)> deleter;
		std::vector<std::shared_ptr<T>> ptrs;

	public:
		VulkanDeleter() : VulkanDeleter([](T, VkAllocationCallbacks*) {}) {}
		VulkanDeleter(VkInstance instance, std::function<void(VkInstance, T, VkAllocationCallbacks*)> deletef)
		{
			this->deleter = [&instance, deletef](T obj) { deletef(instance.getHandle(), obj, nullptr); };
		}

		VulkanDeleter(VkDevice device, std::function<void(VkDevice, T, VkAllocationCallbacks*)> deletef)
		{
			this->deleter = [&device, deletef](T obj) { deletef(device, obj, nullptr); };
		}

		VulkanDeleter(std::initializer_list<std::shared_ptr<T>> ptrs) : VulkanDeleter()
		{
			for (auto & ptr : ptrs) {
				this->ptrs.push_back(ptr);
			}
		}

		VulkanDeleter(const VulkanDeleter<T> &vd) = delete;
		VulkanDeleter(VulkanDeleter<T> &&vd)
		{
			cleanup();
			object = vd.object;
			vd.object = VK_NULL_HANDLE;
		}

		VulkanDeleter<T>& operator=(const VulkanDeleter<T> &vd) = delete;
		VulkanDeleter<T>& operator=(VulkanDeleter<T> &&vd)
		{
			if (this != &vd)
			{
				cleanup();
				object = vd.object;
				vd.object = VK_NULL_HANDLE;
			}

			return *this;
		}

		const T* operator &() const {
			return &object;
		}

		T* replace() {
			cleanup();
			return &object;
		}

		operator T() const {
			return object;
		}

		T& operator=(T rhs) {
			if (rhs != object) {
				cleanup();
				object = rhs;
			}

			return object;
		}


		template<typename V>
		bool operator==(V rhs) {
			return object == T(rhs);
		}

		~VulkanDeleter()
		{
			cleanup();
		}
	private:
		void cleanup()
		{
			if (object != VK_NULL_HANDLE) {
				deleter(object);
			}
			object = VK_NULL_HANDLE;
		}

	};
}


#endif //DEVA_FRAMEWORK_GRAPHICS_VULKAN_VULKAN_DELETER_HPP