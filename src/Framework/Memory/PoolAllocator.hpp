#ifndef DEVA_MEMORY_POOL_ALLOCATOR_H
#define DEVA_MEMORY_POOL_ALLOCATOR_H

#include "Allocator.hpp"

namespace DevaFramework
{

class PoolAllocator : public Allocator
{
public:

    static const std::size_t MAX_MEMORY = (268435456); /// Maximum contiguous memory that can be alloc'd = 256MB
    static const std::size_t PTR_SIZE = sizeof(char*);

    std::size_t max_chunk_size;
    bool isFreed = false;

private:
    std::size_t ALLOCATED_MEMORY;

    Memory _start;
    mutable Memory next;

public:
    explicit PoolAllocator();

    explicit PoolAllocator(std::size_t size_bytes, std::size_t maximum_object_size);


    Memory allocate(std::size_t _size) const;

    bool deallocate(Memory ptr) const;

    void free_all();

    ~PoolAllocator();
};
}

#endif // DEVA_MEMORY_POOL_ALLOCATOR_H
