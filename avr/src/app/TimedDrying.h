//
// Created by ghisi on 12/30/22.
//

#ifndef AVR_TIMEDDRYING_H
#define AVR_TIMEDDRYING_H


#include "../system/EventHandler.h"
#include "../system/MessageDispatcher.h"
#include "Application.h"
#include "../time/TimeTick.h"

class TimedDrying: public EventHandler, public Application {
public:
    explicit TimedDrying(MessageDispatcher* messageDispatcher);
    bool handle(Message* event) override;
    void stop() override;
    void toForeground() override;
    void toBackground() override;
    void renderUI() override;

private:
    enum State {
        MINUTES, SECONDS, NONE
    };
    void updateTimestamp(TimeTick *timeTick);
    void updateCountdown(TimeTick *timeTick);
    void handleUserInput(Message* event);
    MessageDispatcher *messageDispatcher;
    uint32_t previousTimestamp;
    uint16_t milliseconds;
    int8_t seconds;
    int8_t minutes;
    int8_t setSeconds;
    int8_t setMinutes;
    State state = State::NONE;
    static constexpr MessageType messageTypes[] = {TIME_TICK, USER_INPUT};
    static constexpr uint8_t messageTypeCount = 2;

    void renderCountdown();

    void renderSetTimer();
};


#endif //AVR_TIMEDDRYING_H
