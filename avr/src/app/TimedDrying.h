//
// Created by ghisi on 12/30/22.
//

#ifndef AVR_TIMEDDRYING_H
#define AVR_TIMEDDRYING_H


#include "../system/EventHandler.h"

class TimedDrying: public EventHandler {
public:
    TimedDrying();
    EventType eventType() override;
    bool handle(std::unique_ptr<Event> event) override;
    void activate();
    void deactivate();
private:
    enum class State {
        NONE, MINUTES, SECONDS
    };
    void handleTimeTick(std::unique_ptr<Event> event);
    void handleUserInput(std::unique_ptr<Event> event);
    uint32_t previousTimestamp;
    uint8_t seconds;
    uint8_t minutes;
    uint8_t setSeconds;
    uint8_t setMinutes;
    bool active;
};


#endif //AVR_TIMEDDRYING_H
