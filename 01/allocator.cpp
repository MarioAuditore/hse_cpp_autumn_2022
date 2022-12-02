#include "allocator.hpp"

using namespace allocator;

void Allocator::freeMemory()
{
    offset = nullptr;
    delete[] this->memory;

    max_memory = 0;
    used_memory = 0;
}

void Allocator::makeAllocator(std::size_t maxSize)
{
    if (this->memory != nullptr) {
        this->freeMemory();
    }
    else {
        offset = nullptr;
        used_memory = 0;
    }

    memory = new char[maxSize];
    offset = memory;
    max_memory = maxSize;
}

char* Allocator::alloc(std::size_t size)
{
    char* return_memory;

    if (used_memory + size <= max_memory) {
        // возвращаем начало куска памяти
        return_memory = offset;
        // увеличиваем размер занятой памяти
        offset += size; 
        used_memory += size;
    }
    else 
    {
        // недостаточно места
        return_memory = nullptr;
    }
    return return_memory;
}

void Allocator::reset()
{
    used_memory = 0;
    offset = memory;
}