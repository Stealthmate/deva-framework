#ifndef DEVA_ENGINE_GRAPHICS_VULKAN_BUFFER_MEMORY_INDEX_HPP
#define DEVA_ENGINE_GRAPHICS_VULKAN_BUFFER_MEMORY_INDEX_HPP

#include "Config.hpp"

#include <map>

namespace DevaEngine {


	class VulkanBufferMemoryIndex {
	public:
		typedef DevaFramework::Uuid BufID;
		typedef DevaFramework::Uuid MemID;

		DEVA_ENGINE_API BufID addBuffer(DevaFramework::VulkanBuffer &&buffer, const DevaFramework::Uuid &memory = DevaFramework::Uuid::NULL_ID);
		DEVA_ENGINE_API MemID addMemory(DevaFramework::VulkanMemory &&memory);
		DEVA_ENGINE_API void bindBufferMemory(const BufID &bufID, const MemID &memID, const DevaFramework::VulkanDevice &dev, VkDeviceSize offset = 0);

		DEVA_ENGINE_API DevaFramework::VulkanBuffer& getBuffer(const BufID &id);
		DEVA_ENGINE_API const DevaFramework::VulkanBuffer& getBuffer(const BufID &id) const;
		DEVA_ENGINE_API DevaFramework::VulkanMemory& getMemory(const MemID &id);
		DEVA_ENGINE_API const DevaFramework::VulkanMemory& getMemory(const MemID &id) const;

		DEVA_ENGINE_API MemID getBufferMemory(const BufID &bufID);
		
		DEVA_ENGINE_API std::unordered_set<MemID> getUnmappedMemoryBlocks() const;
		DEVA_ENGINE_API std::unordered_set<BufID> getUnmappedBuffers() const;

		DEVA_ENGINE_API void unbindBufferMemory(const BufID &bufID, const MemID &memID);

		DEVA_ENGINE_API void removeBuffer(const BufID &id, bool discardMemory);
		DEVA_ENGINE_API void removeMemory(const MemID &id);

		DEVA_ENGINE_API std::pair<std::vector<DevaFramework::VulkanBuffer>, std::vector<DevaFramework::VulkanMemory>> purge();
		DEVA_ENGINE_API std::pair<std::vector<DevaFramework::VulkanBuffer>, std::vector<DevaFramework::VulkanMemory>> clear(bool discardResources);

	private:

		class MemoryComparator {
		public:
			bool operator()(const DevaFramework::VulkanMemory* lhs, const DevaFramework::VulkanMemory* rhs) const;
		};

		bool needsPurge = false;

		std::unordered_set<BufID> bufferIDs;
		std::unordered_set<MemID> memoryIDs;
		std::unordered_map<BufID, DevaFramework::VulkanBuffer> bufferIDMap;
		std::unordered_map<MemID, DevaFramework::VulkanMemory> memoryIDMap;
		std::map<DevaFramework::VulkanMemory*, MemID, MemoryComparator> sortedMemoryMap;
		std::unordered_map<BufID, MemID> bufferToMemoryMap;
		std::unordered_map<MemID, std::unordered_set<BufID>> memoryToBuffersMap;

		DevaFramework::VulkanBuffer eraseBuffer(const BufID &id);
		DevaFramework::VulkanMemory eraseMemory(const MemID &id);

	
	};

}


#endif // DEVA_ENGINE_GRAPHICS_VULKAN_BUFFER_MEMORY_INDEX_HPP