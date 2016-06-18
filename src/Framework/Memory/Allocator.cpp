#include "Allocator.hpp"

#include <assert.h>
#include <iostream>
#include <cstdlib>

using namespace DevaFramework;

Allocator::Allocator()
{
    this->nAllocs = 0;
}

Allocator::Allocator(Allocator &&alloc)
{
    this->nAllocs = alloc.nAllocs;
}

Allocator& Allocator::operator=(Allocator &&alloc)
{
    this->nAllocs = alloc.nAllocs;
    return *this;
}

Allocator::~Allocator()
{
}
