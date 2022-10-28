//
// Created by ghisi on 09.10.22.
//

#ifndef AVR_EVENTTYPE_H
#define AVR_EVENTTYPE_H


enum EventType {
    FRAME_RECEIVED,
    PACKET_RECEIVED,
    PACKET_DISPATCHED,
    PING_RECEIVED,
    CPU_STATS_DISPATCHED,
    MEMORY_STATS_DISPATCHED,
    SHOW_TEXT_REQUESTED,
    ASYNC_SCHEDULED,
    ASYNC_CHAIN_SCHEDULED,
    MAX,
};


#endif //AVR_EVENTTYPE_H
