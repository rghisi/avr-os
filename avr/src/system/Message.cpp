//
// Created by ghisi on 09.10.22.
//

#include "Message.h"

Message::Message(MessageType type) {
    this->eType = type;
}

Message::~Message() = default;

MessageType Message::type() {
    return eType;
}

