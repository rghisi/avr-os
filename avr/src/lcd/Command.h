//
// Created by ghisi on 12/31/22.
//

#ifndef AVR_COMMAND_H
#define AVR_COMMAND_H


class Command {
public:
    enum class Type {
        DRAW_TEXT,
        ENABLE_CURSOR,
        DISABLE_CURSOR
    };
    explicit Command(Type type);
    virtual ~Command() = default;
    Command::Type type;
};


#endif //AVR_COMMAND_H
