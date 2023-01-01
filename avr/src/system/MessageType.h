//
// Created by ghisi on 09.10.22.
//

#ifndef AVR_MESSAGETYPE_H
#define AVR_MESSAGETYPE_H


enum MessageType {
    TIME_TICK,
    DISPLAY_COMMAND,
    ASYNC_SCHEDULED,
    ASYNC_CHAIN_SCHEDULED,
    USER_INPUT,
    BME280_REPORT,
    MAX,
};


#endif //AVR_MESSAGETYPE_H
