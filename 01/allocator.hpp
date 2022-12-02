#pragma once
#include <iostream>

namespace allocator 
{
    class Allocator
    {
        public:
        
        char* memory;
        char* offset;
        size_t max_memory;
        size_t used_memory;

        void freeMemory();
        

        void makeAllocator(std::size_t maxSize);

        char* alloc(std::size_t size);

        void reset();

        // Это деструктор!
        ~Allocator()
        {
            this->freeMemory();
        };

    };
}