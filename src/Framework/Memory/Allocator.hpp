#ifndef DEVA_FRAMEWORK_MEMORY_ALLOCATOR_H
#define DEVA_FRAMEWORK_MEMORY_ALLOCATOR_H

#include "Config.hpp"

namespace DevaFramework
{

class Allocator
{

public:

    mutable std::size_t nAllocs = 0;

    virtual Memory allocate(std::size_t _size) const=0;
    virtual bool deallocate(Memory p) const=0;

    Allocator();

    Allocator(const Allocator &alloc) =delete;
    Allocator(Allocator &&alloc);
    virtual Allocator& operator=(const Allocator &alloc) =delete;
    virtual Allocator& operator=(Allocator &&alloc);

    virtual ~Allocator();
};

}

#endif // DEVA_FRAMEWORK_MEMORY_ALLOCATOR_H
