#include "Subrenderer.hpp"

using namespace DevaFramework;
using namespace DevaEngine;

VulkanRenderDrawer::VulkanRenderDrawer(const VulkanDevice &dev, const DevaFramework::VulkanQueue &queue)
	: device(dev), renderQueue(queue) {

}