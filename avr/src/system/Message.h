//
// Created by ghisi on 09.10.22.
//

#ifndef AVR_MESSAGE_H
#define AVR_MESSAGE_H

#include "MessageType.h"
#include "memory"

class Message {
public:
    explicit Message(MessageType type);
    virtual ~Message();
    MessageType type();

private:
    MessageType eType;
};


#endif //AVR_MESSAGE_H
