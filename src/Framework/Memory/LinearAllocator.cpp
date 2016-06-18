#include "LinearAllocator.hpp"

#include <malloc.h>
#include <assert.h>
#include <iostream>

using namespace DevaFramework;

LinearAllocator::LinearAllocator() : Allocator()
{
    this->next_free = 0;
    _start = 0;
    ALLOCATED_MEMORY = 0;
    USED_MEMORY = 0;
    nAllocs = 0;
}

LinearAllocator::LinearAllocator(std::size_t size) : Allocator()
{
    _start = (Memory)malloc(size);
    assert(_start);
    next_free = _start;
    ALLOCATED_MEMORY = size;
    USED_MEMORY = 0;
    nAllocs = 0;
}

LinearAllocator::LinearAllocator(LinearAllocator &&linAlloc) : Allocator(std::move(linAlloc))
{
    if(_start) free(_start);
    this->_start = linAlloc._start;
    this->next_free = linAlloc.next_free;
    this->ALLOCATED_MEMORY = linAlloc.ALLOCATED_MEMORY;
    this->USED_MEMORY = linAlloc.USED_MEMORY;
}

LinearAllocator& LinearAllocator::operator=(LinearAllocator &&linAlloc)
{
    Allocator::operator=(std::move(linAlloc));
    if(_start) free(_start);
    this->_start = linAlloc._start;
    this->next_free = linAlloc.next_free;
    this->ALLOCATED_MEMORY = linAlloc.ALLOCATED_MEMORY;
    this->USED_MEMORY = linAlloc.USED_MEMORY;

    return *this;
}

Memory LinearAllocator::allocate(std::size_t size) const
{
    if(ALLOCATED_MEMORY - USED_MEMORY < size)
    {
        std::cerr << "No available memory in linear allocator. Returning null.\n";
        return 0;
    }

    Memory alloc = next_free;
    next_free+=size;
    USED_MEMORY+=size;
    nAllocs++;
    return alloc;
}

bool LinearAllocator::deallocate(Memory p) const
{
    return true;
}

LinearAllocator::~LinearAllocator()
{
    if(_start) free(_start);
    ALLOCATED_MEMORY = 0;
    USED_MEMORY = 0;
    nAllocs = 0;
}
