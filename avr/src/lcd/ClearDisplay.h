//
// Created by ghisi on 1/2/23.
//

#ifndef AVR_CLEARDISPLAY_H
#define AVR_CLEARDISPLAY_H


#include "DisplayCommand.h"

class ClearDisplay: public DisplayCommand {
public:
    ~ClearDisplay() override = default;
    void command(Display *display) override;
};


#endif //AVR_CLEARDISPLAY_H
