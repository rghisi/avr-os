//
// Created by ghisi on 27.10.22.
//

#ifndef AVR_MEMORYSTATS_H
#define AVR_MEMORYSTATS_H


#include "cstdint"
#include "Event.h"

class MemoryStats: public Event {
public:
    MemoryStats(uint32_t value);
    ~MemoryStats() override;
    uint32_t value;
};


#endif //AVR_MEMORYSTATS_H
