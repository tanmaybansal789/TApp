#ifndef ALLOCATOR_TPP
#define ALLOCATOR_TPP

#include <cassert>

namespace TApp {

    template <typename T>
    PoolAllocator<T>::PoolAllocator(size_t poolSize)
        : poolSize(poolSize), elementSize(sizeof(T)), memoryPool(nullptr), freeList(nullptr) {
        initializePool();
    }

    template <typename T>
    PoolAllocator<T>::~PoolAllocator() {
        ::operator delete(memoryPool);
    }

    template <typename T>
    template <typename U, typename... Args>
    U* PoolAllocator<T>::allocate(Args&&... args) {
        constexpr size_t requiredSize = sizeof(U);
        if (requiredSize > elementSize) {
            // Allocate additional memory if U is larger than T
            size_t adjustedPoolSize = poolSize * (requiredSize / elementSize + (requiredSize % elementSize != 0 ? 1 : 0));
            initializePool(adjustedPoolSize, requiredSize);
        }

        assert(freeList != nullptr && "PoolAllocator is out of memory!");

        // Take the first free block
        U* allocatedBlock = reinterpret_cast<U*>(freeList);
        freeList = *reinterpret_cast<void**>(freeList);

        // Construct the object in place
        return new (allocatedBlock) U(std::forward<Args>(args)...);
    }

    template <typename T>
    void PoolAllocator<T>::deallocate(T* p) {
        if (p != nullptr) {
            // Call the destructor explicitly
            p->~T();

            // Add the block back to the free list
            *reinterpret_cast<void**>(p) = freeList;
            freeList = p;
        }
    }

    template <typename T>
    void PoolAllocator<T>::initializePool(size_t adjustedPoolSize, size_t adjustedElementSize) {
        // Adjust poolSize and elementSize if larger elements are needed
        if (adjustedPoolSize != poolSize || adjustedElementSize != elementSize) {
            poolSize = adjustedPoolSize;
            elementSize = adjustedElementSize;
        }

        // Allocate the memory pool
        memoryPool = reinterpret_cast<T*>(::operator new(poolSize * elementSize));

        // Initialize the free list
        freeList = memoryPool;
        for (size_t i = 0; i < poolSize - 1; ++i) {
            void* nextBlock = reinterpret_cast<void*>(reinterpret_cast<char*>(memoryPool) + (i + 1) * elementSize);
            *reinterpret_cast<void**>(reinterpret_cast<void*>(reinterpret_cast<char*>(memoryPool) + i * elementSize)) = nextBlock;
        }
        // The last block points to nullptr
        *reinterpret_cast<void**>(reinterpret_cast<void*>(reinterpret_cast<char*>(memoryPool) + (poolSize - 1) * elementSize)) = nullptr;
    }

    template <typename T>
    void PoolAllocator<T>::initializePool() {
        initializePool(poolSize, elementSize);
    }

}

#endif // ALLOCATOR_TPP