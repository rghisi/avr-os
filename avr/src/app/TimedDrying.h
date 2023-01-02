//
// Created by ghisi on 12/30/22.
//

#ifndef AVR_TIMEDDRYING_H
#define AVR_TIMEDDRYING_H


#include "../system/EventHandler.h"
#include "../system/Messaging.h"
#include "Application.h"
#include "../time/TimeTick.h"
#include "../sensors/ClimateReport.h"

class TimedDrying: public EventHandler, public Application {
public:
    explicit TimedDrying(Messaging* messageDispatcher);
    bool handle(Message* event) override;
    void toForeground() override;
    void toBackground() override;
private:
    enum Selection: int8_t {
        NONE = 0, TEMPERATURE, MINUTES, SECONDS, MAX
    };
    enum class State {
        STOPPED, RUNNING, FINISHED
    };
    static constexpr MessageType messageTypes[] = {TIME_TICK, USER_INPUT, CLIMATE_REPORT};
    static constexpr uint8_t messageTypeCount = 3;
    static constexpr uint8_t TIMER_X_POSITION = 10;
    static constexpr uint8_t CLIMATE_X_POSITION = 0;
    static constexpr uint8_t SET_POINT_Y_POSITION = 0;
    static constexpr uint8_t CURRENT_VALUES_Y_POSITION = 1;
    Messaging *messaging;
    Selection selection = Selection::NONE;
    State countdownState = State::STOPPED;
    uint8_t cursorX = TIMER_X_POSITION + 1;
    uint32_t previousTimestamp;
    uint16_t milliseconds;
    int8_t seconds;
    int8_t minutes;
    int8_t setSeconds;
    int8_t setMinutes;
    uint8_t setTemperature;
    uint8_t temperature;
    uint8_t humidity;
    void renderUI();
    void updateTimestamp(TimeTick *timeTick);
    void updateCountdown(TimeTick *timeTick);
    void handleUserInput(Message* event);
    void renderCountdown();
    void renderSetTimer();
    void renderCursor();
    void changeUISelection(int8_t amount);
    void changeSelection(int8_t amount);
    void startStop();
    void finish();
    void start();
    void renderSetClimate();
    void handleClimateReport(ClimateReport *climateReport);
    void renderClimate();
    static int8_t max(int8_t a, int8_t b);
    static int8_t min(int8_t a, int8_t b);

    void stop();

    void resetCountdown();
};


#endif //AVR_TIMEDDRYING_H
