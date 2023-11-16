//
// Created by ghisi on 22.03.23.
//

#ifndef AVR_MEMORYALLOCATOR_H
#define AVR_MEMORYALLOCATOR_H


#include "cstdint"
#include "cstddef"

enum class AllocationFlags { FREE = 0x00, USED = 0xFF };

class Allocation {
public:
    explicit Allocation(size_t size) {
        this->size = size + sizeof(Allocation);
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

class MemoryStats {
public:
    size_t size;
    size_t used;
    size_t free;
    size_t usedBlocks;
    size_t freeBlocks;
    size_t delta;
};

template <size_t S>
class MemoryAllocator {
public:
    constexpr static size_t AllocationOverhead = sizeof(Allocation);
    MemoryAllocator();
    uintptr_t *allocate(size_t requestedBytes);
    void free(void *ptr);
    MemoryStats *stats();

private:
    constexpr static unsigned floorlog2(unsigned x) {
        return x < 2 ? x : 1+floorlog2(x >> 1);
    }
    constexpr static auto MinimumAllocationSize = sizeof(uintptr_t);
    constexpr static auto MemoryPositions = S / MinimumAllocationSize;
    constexpr static auto MinimumAllocationSizePower = floorlog2(MinimumAllocationSize) - 1;

    Allocation *allocationList = nullptr;
    MemoryStats memoryStats = MemoryStats();
    uintptr_t memory[MemoryPositions] = {};

    Allocation *merge(Allocation *left, Allocation *right);

    [[nodiscard]] Allocation *findBestAllocation(size_t size) const;
};

#endif //AVR_MEMORYALLOCATOR_H
