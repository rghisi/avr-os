//
// Created by ghisi on 1/2/23.
//

#ifndef AVR_DISABLECURSOR_H
#define AVR_DISABLECURSOR_H


#include "DisplayCommand.h"

class DisableCursor: public DisplayCommand {
    void command(Display *display) override;
};


#endif //AVR_DISABLECURSOR_H
