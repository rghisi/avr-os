//
// Created by ghisi on 12/30/22.
//

#ifndef AVR_TIMEDDRYING_H
#define AVR_TIMEDDRYING_H


#include "../system/Subscriber.h"
#include "../system/Messaging.h"
#include "Application.h"
#include "../time/TimeTick.h"
#include "../sensors/ClimateReport.h"
#include "../time/TimerState.h"
#include "../input/UserInput.h"
#include "../tasks/TemperatureControlStatus.h"

class TimedDrying: public Subscriber, public Application {
public:
    explicit TimedDrying(Messaging* messageDispatcher, Timer *timer);
    void handle(Message* event) override;
    void toForeground() override;
    void toBackground() override;
    char *title() override;

private:
    enum Selection: int8_t {
        NONE = 0, TEMPERATURE, MINUTES, SECONDS, MAX
    };
    enum class State {
        STOPPED, RUNNING, FINISHED
    };
    static constexpr uint8_t TIMER_X_POSITION = 10;
    static constexpr uint8_t CLIMATE_X_POSITION = 0;
    static constexpr uint8_t SET_POINT_Y_POSITION = 0;
    static constexpr uint8_t CURRENT_VALUES_Y_POSITION = 1;
    Messaging *messaging;
    Timer *timer;
    Selection selection = Selection::NONE;
    State countdownState = State::STOPPED;
    uint8_t cursorX = TIMER_X_POSITION + 1;
    int8_t seconds;
    int8_t minutes;
    int8_t setSeconds;
    int8_t setMinutes;
    int8_t setTemperature;
    void startStop();
    void finish();
    void start();
    void stop();
    void cycleSelection(int8_t amount);
    void changeSelected(int8_t amount);
    void handleTimerState(TimerState *timerState);
    void handleUserInput(UserInput* userInput);
    void handleTemperatureControlStatus(TemperatureControlStatus *temperatureControlStatus);
    void handleClimateReport(ClimateReport *climateReport);
    void renderUI();
    void renderCountdown();
    void renderSetTimer();
    void renderCursor();
    void renderSetClimate();
    void renderClimate();
    void renderStatus();
};


#endif //AVR_TIMEDDRYING_H
