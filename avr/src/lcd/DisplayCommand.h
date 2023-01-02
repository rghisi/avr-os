//
// Created by ghisi on 12/31/22.
//

#ifndef AVR_DISPLAYCOMMAND_H
#define AVR_DISPLAYCOMMAND_H


#include "../system/Message.h"
#include "Display.h"
#include "functional"

class DisplayCommand: public Message {
public:
    explicit DisplayCommand();
    virtual void command(Display *display) = 0;
};


#endif //AVR_DISPLAYCOMMAND_H
