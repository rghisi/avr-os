//
// Created by ghisi on 12/31/22.
//

#ifndef AVR_DISPLAYTEXTCOMMAND_H
#define AVR_DISPLAYTEXTCOMMAND_H


#include "../system/Event.h"

class DisplayTextCommand: public Event {
public:
    explicit DisplayTextCommand(char *text);
    ~DisplayTextCommand() override;
    char *text;
};


#endif //AVR_DISPLAYTEXTCOMMAND_H
