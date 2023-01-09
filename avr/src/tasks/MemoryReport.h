//
// Created by ghisi on 1/9/23.
//

#ifndef AVR_MEMORYREPORT_H
#define AVR_MEMORYREPORT_H


#include "../system/Message.h"

class MemoryReport: public Message {
public:
    explicit MemoryReport(uint16_t freeMemory);
    uint16_t freeMemory;
};


#endif //AVR_MEMORYREPORT_H
