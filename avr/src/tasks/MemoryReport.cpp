//
// Created by ghisi on 1/9/23.
//

#include "MemoryReport.h"

MemoryReport::MemoryReport(uint16_t freeMemory): Message(MessageType::MEMORY_REPORT) {
    this->freeMemory = freeMemory;
}
