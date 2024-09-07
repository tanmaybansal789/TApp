#ifndef POOL_ALLOCATOR_H
#define POOL_ALLOCATOR_H

#include <cstddef>
#include <new>

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
        void initialisePool(size_t adjustedPoolSize, size_t adjustedElementSize);
        void initialisePool();

    private:
        T* memoryPool;
        void* freeList;
        size_t poolSize;
        size_t elementSize;

    };
}

#include "Utils/Memory/PoolAllocator/PoolAllocator.tpp"

#endif // POOL_ALLOCATOR_H