#include "VulkanBufferMemoryIndex.hpp"

#include <algorithm>

using namespace DevaFramework;
using namespace DevaEngine;

#define BUFFER_NOT_FOUND(id) DevaInvalidArgumentException(strformat("Buffer with ID: {} does not exist in index", id.str()));
#define MEMORY_NOT_FOUND(id) DevaInvalidArgumentException(strformat("Memory with ID: {} does not exist in index", id.str()));

typedef VulkanBufferMemoryIndex::BufID BufID;
typedef VulkanBufferMemoryIndex::MemID MemID;

bool VulkanBufferMemoryIndex::MemoryComparator::operator()(const VulkanMemory* lhs, const VulkanMemory* rhs) const {
	return lhs->size < rhs->size;
}

BufID VulkanBufferMemoryIndex::addBuffer(VulkanBuffer &&buffer, const Uuid & memory) {


	Uuid id;
	while (bufferIDs.find(id) != bufferIDs.end()) id = Uuid();

	bufferIDs.insert(id);
	bufferIDMap.insert({ id, std::move(buffer) });

	if (memory == Uuid::NULL_ID)
		return id;

	auto iMem = memoryIDs.find(memory);
	if (iMem == memoryIDs.end()) {
		throw MEMORY_NOT_FOUND(memory);
	}

	bufferToMemoryMap.insert({ id, memory });
	memoryToBuffersMap.find(memory)->second.insert(id);

	return id;
}

MemID VulkanBufferMemoryIndex::addMemory(VulkanMemory &&memory) {
	Uuid id;
	while (memoryIDs.find(id) != memoryIDs.end()) id = Uuid();

	memoryIDs.insert(id);
	memoryIDMap.insert({ id, std::move(memory) });
	//sortedMemoryMap.insert({ &memoryIDMap.find(id)->second, id });
	memoryToBuffersMap.insert({ id,{} });

	return id;
}

void VulkanBufferMemoryIndex::bindBufferMemory(const BufID & bufID, const MemID & memID, const VulkanDevice & dev, VkDeviceSize offset) {

	auto iBuf = bufferIDMap.find(bufID);
	if (iBuf == bufferIDMap.end()) {
		throw BUFFER_NOT_FOUND(bufID);
	}
	auto iMem = memoryIDMap.find(memID);
	if (iMem == memoryIDMap.end()) {
		throw MEMORY_NOT_FOUND(memID);
	}

	auto iMappedMem = bufferToMemoryMap.find(iBuf->first);
	if (iMappedMem != bufferToMemoryMap.end()) {
		throw DevaInvalidArgumentException(strformat("Buffer {} has already been mapped to memory {}", bufID.str(), iMappedMem->second.str()));
	}

	auto device = dev.handle;
	auto &vk = dev.vk;
	VkResult result = vk.vkBindBufferMemory(device, iBuf->second.handle, iMem->second.handle, offset);
	if (result != VK_SUCCESS) {
		throw DevaExternalFailureException("Vulkan", strformat("Could not bind buffer handle {} to memory handle {}", strm(iBuf->second.handle), strm(iMem->second.handle)));
	}

	bufferToMemoryMap.insert({ bufID, memID });

	auto iMemBufMap = memoryToBuffersMap.find(memID);
	iMemBufMap->second.insert(bufID);
}

VulkanBuffer & VulkanBufferMemoryIndex::getBuffer(const BufID & id) {
	auto i = bufferIDs.find(id);
	if (i == bufferIDs.end()) {
		throw BUFFER_NOT_FOUND(id);
	}

	return bufferIDMap.find(id)->second;
}

const VulkanBuffer & VulkanBufferMemoryIndex::getBuffer(const BufID & id) const {
	auto i = bufferIDs.find(id);
	if (i == bufferIDs.end()) {
		throw BUFFER_NOT_FOUND(id);
	}

	return bufferIDMap.find(id)->second;
}

VulkanMemory & VulkanBufferMemoryIndex::getMemory(const MemID &id) {
	auto i = memoryIDs.find(id);
	if (i == memoryIDs.end()) {
		throw MEMORY_NOT_FOUND(id);
	}

	return memoryIDMap.find(id)->second;
}

const VulkanMemory & VulkanBufferMemoryIndex::getMemory(const MemID & id) const {
	auto i = memoryIDs.find(id);
	if (i == memoryIDs.end()) {
		throw MEMORY_NOT_FOUND(id);
	}

	return memoryIDMap.find(id)->second;
}

MemID VulkanBufferMemoryIndex::getBufferMemory(const BufID & bufID) {
	auto i = bufferIDs.find(bufID);
	if (i == bufferIDs.end()) {
		throw BUFFER_NOT_FOUND(bufID);
	}

	auto result = bufferToMemoryMap.find(bufID);
	if (result == bufferToMemoryMap.end()) return Uuid::NULL_ID;
	return result->second;
}

std::unordered_set<MemID> VulkanBufferMemoryIndex::getUnmappedMemoryBlocks() const {
	std::unordered_set<MemID> mems;
	
	typedef struct {
		bool operator()(const MemID &id, const std::pair<MemID, std::unordered_set<BufID>> &idpair) {
			return id == idpair.first;
		}

		bool operator()(const std::pair<MemID, std::unordered_set<BufID>> &idpair, const MemID &id) {
			return !(*this)(id, idpair);
		}
		bool operator()(const MemID &id1, const MemID &id2) {
			return id1 < id2;
		}
		bool operator()(const std::pair<MemID, std::unordered_set<BufID>> &id1, const std::pair<MemID, std::unordered_set<BufID>> &id2) {
			return id1.first < id2.first;
		}
	} cmp;

	std::set_difference(
		memoryIDs.begin(), 
		memoryIDs.end(), 
		memoryToBuffersMap.begin(), 
		memoryToBuffersMap.end(), 
		std::inserter(mems, mems.end()), 
		cmp());
	return mems;
}

std::unordered_set<BufID> VulkanBufferMemoryIndex::getUnmappedBuffers() const {
	std::unordered_set<BufID> bufs;

	typedef struct {
		bool operator()(const BufID &id, const std::pair<BufID, MemID> &idpair) {
			return id < idpair.first;
		}

		bool operator()(const std::pair<BufID, MemID> &idpair, const BufID &id) {
			return (*this)(id, idpair);
		}

		bool operator()(const BufID &id1, const BufID &id2) {
			return id1 < id2;
		}
		bool operator()(const std::pair<BufID, MemID> &id1, const std::pair<BufID, MemID> &id2) {
			return id1.first < id2.first;
		}

	} cmp;

	std::set_difference(
		bufferIDs.begin(),
		bufferIDs.end(),
		bufferToMemoryMap.begin(),
		bufferToMemoryMap.end(),
		std::inserter(bufs, bufs.end()),
		cmp());
	return bufs;
}

void VulkanBufferMemoryIndex::unbindBufferMemory(const BufID & bufID, const MemID & memID)
{
	auto i = bufferToMemoryMap.find(bufID);
	if (i == bufferToMemoryMap.end()) {
		throw DevaInvalidArgumentException(strformat("Buffer {} is not bound to {} memory", bufID.str(), memID.str()));
	}

	bufferToMemoryMap.erase(i);

	auto j = memoryToBuffersMap.find(memID);
	if (j == memoryToBuffersMap.end()) {
		throw DevaInvalidArgumentException(strformat("Memory {} is not bound to {} buffer", memID.str(), bufID.str()));
	}

	memoryToBuffersMap.erase(j);
}

void VulkanBufferMemoryIndex::removeBuffer(const BufID &id, bool discardMemory) {
	auto iBuf = bufferIDs.find(id);
	if (iBuf == bufferIDs.end()) {
		throw BUFFER_NOT_FOUND(id);
	}

	auto iBufMem = bufferToMemoryMap.find(id);
	Uuid memID = iBufMem->second;

	auto iMemBuf = memoryToBuffersMap.find(memID);
	iMemBuf->second.erase(id);
	if (discardMemory && iMemBuf->second.size() == 0) {
		removeMemory(memID);
	}
	bufferToMemoryMap.erase(iBufMem);
	bufferIDs.erase(iBuf);
	needsPurge = true;
}

void VulkanBufferMemoryIndex::removeMemory(const MemID &id) {
	auto iMem = memoryIDs.find(id);
	if (iMem == memoryIDs.end()) {
		throw MEMORY_NOT_FOUND(id);
	}

	auto iMemBuf = memoryToBuffersMap.find(id);

	if (iMemBuf != memoryToBuffersMap.end() && iMemBuf->second.size() > 0) {
		throw DevaInvalidArgumentException(strformat("Memory {} is still bound to {} buffers", id.str(), iMemBuf->second.size()));
	}

	memoryToBuffersMap.erase(iMemBuf);
	memoryIDs.erase(id);
	needsPurge = true;
}

VulkanBuffer VulkanBufferMemoryIndex::eraseBuffer(const BufID &id) {
	bufferIDs.erase(id);
	VulkanBuffer buf;

	auto i = bufferIDMap.find(id);
	if (i != bufferIDMap.end()) {
		buf = std::move(i->second);
		bufferIDMap.erase(i);
	}

	return buf;
}

VulkanMemory VulkanBufferMemoryIndex::eraseMemory(const MemID &id) {
	memoryIDs.erase(id);
	VulkanMemory mem;

	auto i = memoryIDMap.find(id);
	if (i != memoryIDMap.end()) {
		mem = std::move(i->second);
		memoryIDMap.erase(i);
		//sortedMemoryMap.erase(sortedMemoryMap.find(&mem));
	}

	return mem;
}

std::pair<std::vector<VulkanBuffer>, std::vector<VulkanMemory>> VulkanBufferMemoryIndex::purge() {

	if (!needsPurge) return{};

	std::pair<std::vector<VulkanBuffer>, std::vector<VulkanMemory>> purged;

	auto i = bufferIDMap.begin();
	while (i != bufferIDMap.end()) {
		if (bufferIDs.find(i->first) == bufferIDs.end()) {
			purged.first.push_back(std::move(i->second));
			i = bufferIDMap.erase(i);
		}
		else {
			i++;
		}
	}

	auto j = memoryIDMap.begin();
	while (j != memoryIDMap.end()) {
		if (memoryIDs.find(j->first) == memoryIDs.end()) {
			purged.second.push_back(std::move(j->second));
			j = memoryIDMap.erase(j);
		}
		else {
			j++;
		}
	}
	needsPurge = false;

	return purged;
}

std::pair<std::vector<VulkanBuffer>, std::vector<VulkanMemory>> VulkanBufferMemoryIndex::clear() {
	std::pair<std::vector<VulkanBuffer>, std::vector<VulkanMemory>> purged = {};

	bufferIDs.clear();
	memoryIDs.clear();
	needsPurge = true;

	purged = purge();

	bufferIDMap.clear();
	bufferToMemoryMap.clear();
	memoryIDMap.clear();
	memoryToBuffersMap.clear();

	return purged;
}