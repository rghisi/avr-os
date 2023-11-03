//
// Created by ghisi on 22.03.23.
//

#ifndef AVR_MEMORYALLOCATOR_H
#define AVR_MEMORYALLOCATOR_H


#include <cmath>
#include "cstdint"
#include "cstdio"

enum class AllocationFlags { FREE = 0x00, USED = 0xFF };

class Allocation {
public:
    explicit Allocation(size_t size) {
        this->size = size;
        flags = AllocationFlags::FREE;
    }
    size_t size;
    AllocationFlags flags;
    Allocation *previous = nullptr;
    Allocation *next = nullptr;

    [[nodiscard]] bool isFree() const {
        return flags == AllocationFlags::FREE;
    }
};

template <size_t S>
class MemoryAllocator {
public:
    constexpr static auto AllocationOverhead = sizeof(Allocation);
    MemoryAllocator();
    uintptr_t *allocate(size_t requestedBytes);
    void free(void *ptr);
    size_t memoryUsed();
    size_t peakMemoryUsed();
    size_t memoryAvailable();
private:
    constexpr static unsigned floorlog2(unsigned x)
    {
        return x < 2 ? x : 1+floorlog2(x >> 1);
    }
    constexpr static auto MinimumAllocationSize = sizeof(uintptr_t);
    constexpr static auto MemoryPositions = S / MinimumAllocationSize;
    constexpr static auto MinimumAllocationSizePower = floorlog2(MinimumAllocationSize) - 1;
    uintptr_t memory[MemoryPositions] = {};
    Allocation *allocationList = nullptr;
    size_t size = S;
    size_t used = AllocationOverhead;
    size_t peakUsed = AllocationOverhead;

    Allocation *merge(Allocation *left, Allocation *right);
};

#endif //AVR_MEMORYALLOCATOR_H
