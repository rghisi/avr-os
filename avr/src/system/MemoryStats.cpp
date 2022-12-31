//
// Created by ghisi on 12/31/22.
//

#include "MemoryStats.h"

MemoryStats::MemoryStats(uint32_t value) : Event(EventType::MEMORY_STATS_READ) {
    this->value = value;
}

MemoryStats::~MemoryStats() = default;
