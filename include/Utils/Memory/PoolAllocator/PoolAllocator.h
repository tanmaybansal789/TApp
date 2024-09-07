#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <cstddef>   // for std::size_t
#include <new>       // for placement new

namespace TApp {

    template <typename T>
    class PoolAllocator {
    public:
        explicit PoolAllocator(size_t poolSize);
        ~PoolAllocator();

        template <typename U = T, typename... Args>
        U* allocate(Args&&... args);

        void deallocate(T* p);

    private:
        void initializePool(size_t adjustedPoolSize, size_t adjustedElementSize);
        void initializePool();

    private:
        T* memoryPool;
        void* freeList;
        size_t poolSize;
        size_t elementSize;

    };

}

#include "Utils/Memory/PoolAllocator.tpp"

#endif // ALLOCATOR_H