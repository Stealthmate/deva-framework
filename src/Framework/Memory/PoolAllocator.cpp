#include "PoolAllocator.hpp"

#include <malloc.h>
#include <assert.h>
#include <iostream>

using namespace DevaFramework;

PoolAllocator::PoolAllocator() : max_chunk_size(0)
{
	_start = 0;
	next = 0;
	ALLOCATED_MEMORY = 0;
}

PoolAllocator::PoolAllocator(std::size_t size_bytes, std::size_t max_obj_size) :
	max_chunk_size(max_obj_size + PTR_SIZE)
{
	size_bytes = ((size_bytes / max_chunk_size) + 1) * max_chunk_size;

	_start = (Memory)malloc(size_bytes);

	assert(_start);

	ALLOCATED_MEMORY = size_bytes;
	for (Memory i = _start; static_cast<uintptr_t>(i + max_chunk_size - _start) < ALLOCATED_MEMORY; i = i + max_chunk_size)
	{
		*(Memory*)i = i + max_chunk_size;
	}
	Memory last = _start + ALLOCATED_MEMORY - max_chunk_size;
	*(Memory*)last = 0;
	next = *(Memory*)_start;
}

Memory PoolAllocator::allocate(std::size_t _size) const
{
	assert(!isFreed);
	if (_size > max_chunk_size - PTR_SIZE)
	{
		return 0;
	}

	if (!next)
	{
		return 0;
	}

	Memory ret = next;
	next = *(Memory*)next;
	return ret + PTR_SIZE;
}

bool PoolAllocator::deallocate(Memory ptr) const
{
	Memory start_char = _start;

	Memory actual_ptr = ptr - PTR_SIZE;
	Memory actual_ptr_char = actual_ptr;

	bool isPtrValid = actual_ptr_char >= start_char && actual_ptr_char < start_char + ALLOCATED_MEMORY;
	isPtrValid = isPtrValid && ((actual_ptr_char - start_char) % max_chunk_size == 0);
	if (!isPtrValid) return false;

	Memory temp = actual_ptr;
	*(Memory*)temp = next;
	next = temp;
	return true;
}

void PoolAllocator::free_all()
{
	if (_start) free(_start);
}

PoolAllocator::~PoolAllocator()
{
	if (!isFreed && ALLOCATED_MEMORY && _start)
	{
		isFreed = true;
	}
}
