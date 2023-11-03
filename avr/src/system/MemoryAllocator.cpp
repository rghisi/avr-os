//
// Created by ghisi on 22.03.23.
//

#include "MemoryAllocator.h"
#include "memory"

template<size_t S>
MemoryAllocator<S>::MemoryAllocator() {
    auto *memoryStartAddress = &memory[0];
    this->allocationList = new (memoryStartAddress) Allocation(S - AllocationOverhead);
}

template<size_t S>
uintptr_t *MemoryAllocator<S>::allocate(size_t requestedBytes) {
    const auto requestedBytesWithOverhead = requestedBytes + AllocationOverhead;
    const auto remainderBytes = requestedBytesWithOverhead & (MinimumAllocationSize - 1);
    const auto totalBytesRequired = requestedBytesWithOverhead + remainderBytes;

    auto *allocation = allocationList;
    while (allocation != nullptr && (!allocation->isFree() || (allocation->isFree() && allocation->size < totalBytesRequired))) {
        allocation = allocation->next;
    }

    if (allocation == nullptr) {
        return nullptr;
    }

    const auto bytesLeftAfterAllocation = allocation->size - totalBytesRequired;
    used += totalBytesRequired;
    if (used > peakUsed) {
        peakUsed = used;
    }
    allocation->size = totalBytesRequired;
    allocation->flags = AllocationFlags::USED;
    const auto currentAllocationAddress = ((uintptr_t*) std::addressof(*allocation));
    const auto currentAllocationDataAddress = currentAllocationAddress + (AllocationOverhead >> MinimumAllocationSizePower);

    if (bytesLeftAfterAllocation > 0) {
        const auto nextAllocationAddress = currentAllocationAddress + (totalBytesRequired >> MinimumAllocationSizePower);
        const auto freeBlock = new (nextAllocationAddress) Allocation(bytesLeftAfterAllocation - AllocationOverhead);
        freeBlock->next = allocation->next;
        freeBlock->previous = allocation;
        allocation->next = freeBlock;
    }

    return currentAllocationDataAddress;
}

template<size_t S>
void MemoryAllocator<S>::free(void *ptr) {
    const auto dataPointerAddress = (uintptr_t*) ptr;
    const auto allocationAddress = dataPointerAddress - (AllocationOverhead >> MinimumAllocationSizePower);
    auto allocation = (Allocation*) allocationAddress;
    allocation->flags = AllocationFlags::FREE;

    if (allocation->previous != nullptr && allocation->previous->isFree()) {
        allocation = merge(allocation->previous, allocation);
    }
    if (allocation->next != nullptr && allocation->next->isFree()) {
        allocation = merge(allocation, allocation->next);
    }

    if (allocation->previous == nullptr && allocation->next == nullptr) {
        this->used = AllocationOverhead;
    } else {
        this->used -= allocation->size - AllocationOverhead;
    }
}

template<size_t S>
size_t MemoryAllocator<S>::memoryUsed() {
    return used;
}

template<size_t S>
size_t MemoryAllocator<S>::peakMemoryUsed() {
    return peakUsed;
}

template<size_t S>
size_t MemoryAllocator<S>::memoryAvailable() {
    return size - used;
}

template<size_t S>
Allocation *MemoryAllocator<S>::merge(Allocation *left, Allocation *right) {
    left->size += right->size + AllocationOverhead;
    left->next = right->next;
    if (right->next != nullptr) {
        right->next->previous = left;
    }

    return left;
}