#ifndef DEVA_FRAMEWORK_GRAPHICS_VULKAN_VERTEX_INPUT_BINDING_HPP
#define DEVA_FRAMEWORK_GRAPHICS_VULKAN_VERTEX_INPUT_BINDING_HPP

#include "Config.hpp"

#include <vector>

namespace DevaFramework
{
	namespace Vulkan {

		class VertexInputBinding {
			typedef VkVertexInputAttributeDescription Attr;
		public:

			DEVA_FRAMEWORK_API VertexInputBinding(
				uint32_t binding,  
				VkVertexInputRate inputRate, 
				uint32_t stride, 
				const std::vector<Attr> &attrs = {}) : mBinding(binding), mInputRate(inputRate), mStride(stride), mAttributes(attrs) {}

			DEVA_FRAMEWORK_API void addAttribute(const Attr &attr);

			DEVA_FRAMEWORK_API uint32_t binding() const { return mBinding; }
			DEVA_FRAMEWORK_API std::vector<Attr> attributes() const { return mAttributes; }
			DEVA_FRAMEWORK_API uint32_t stride() const { return mStride; }
			DEVA_FRAMEWORK_API VkVertexInputRate inputRate() const { return mInputRate; }


		private:
			uint32_t mBinding;
			VkVertexInputRate mInputRate;
			uint32_t mStride;
			std::vector<Attr> mAttributes;
		};
	}
}

#endif //DEVA_FRAMEWORK_GRAPHICS_VULKAN_VERTEX_INPUT_BINDING_HPP