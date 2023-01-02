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
    CLIMATE_REPORT,
    CLIMATE_CONTROL,
    MAX,
};


#endif //AVR_MESSAGETYPE_H
