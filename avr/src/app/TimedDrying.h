//
// Created by ghisi on 12/30/22.
//

#ifndef AVR_TIMEDDRYING_H
#define AVR_TIMEDDRYING_H


#include "../system/EventHandler.h"
#include "../system/MessageDispatcher.h"

class TimedDrying: public EventHandler {
public:
    explicit TimedDrying(MessageDispatcher* messageDispatcher);
    MessageType eventType() override;
    bool handle(Message* event) override;
    void activate();
    void deactivate();
private:
    enum State {
        MINUTES, SECONDS, NONE
    };
    void handleTimeTick(Message* message);
    void handleUserInput(Message* event);
    MessageDispatcher *messageDispatcher;
    uint32_t previousTimestamp;
    uint8_t seconds;
    uint8_t minutes;
    uint8_t setSeconds;
    uint8_t setMinutes;
    bool active;
    State state = State::NONE;

    void render();
};


#endif //AVR_TIMEDDRYING_H
