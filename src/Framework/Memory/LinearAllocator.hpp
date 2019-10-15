#ifndef DEVA_FRAMEWORK_MEMORY_LINEAR_ALLOCATOR_H
#define DEVA_FRAMEWORK_MEMORY_LINEAR_ALLOCATOR_H

#include "Allocator.hpp"

namespace DevaFramework
{

class LinearAllocator : public Allocator
{
    mutable Memory next_free = 0;

    std::size_t ALLOCATED_MEMORY;
    mutable std::size_t USED_MEMORY;

    Memory _start;

public:

    virtual Memory allocate(std::size_t _size) const override;
    virtual bool deallocate(Memory p) const override;

    LinearAllocator();
    LinearAllocator(std::size_t _size);
    LinearAllocator(LinearAllocator &&linAlloc);

    LinearAllocator& operator=(LinearAllocator &&linAlloc);

    virtual ~LinearAllocator() override;
};


}

#endif // DEVA_FRAMEWORK_MEMORY_LINEAR_ALLOCATOR_H
