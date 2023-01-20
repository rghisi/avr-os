//
// Created by ghisi on 1/2/23.
//

#ifndef AVR_TIMEDMULTITRAYDRYING_H
#define AVR_TIMEDMULTITRAYDRYING_H


#include "../system/Subscriber.h"
#include "Application.h"
#include "../system/Messaging.h"
#include "../time/Timer.h"
#include "../time/TimerState.h"
#include "../sensors/ClimateReport.h"
#include "../input/UserInput.h"
#include "../tasks/TemperatureControlStatus.h"

class TimedMultiTrayDrying: public Subscriber, public Application {
public:
    explicit TimedMultiTrayDrying(Messaging *messaging);
    void handle(Message *event) override;
    void toForeground() override;
    void toBackground() override;
    char *title() override;

private:
    static constexpr uint8_t NUMBER_OF_TRAYS = 4;
    static constexpr uint8_t FIRST_LINE = 0;
    static constexpr uint8_t SECOND_LINE = 1;
    static constexpr uint8_t SET_POINTS_X = 0;
    static constexpr uint8_t TEMPERATURE_X = 8;
    static constexpr uint8_t POWER_X = 12;
    static constexpr uint8_t TIMERS_X = 0;
    static constexpr uint8_t TICK_TOCK_X = 15;
    static constexpr uint8_t MINUTES_CURSOR_X = 2;
    static constexpr uint8_t TEMPERATURE_CURSOR_X = 6;
    static constexpr uint8_t TRAY_A_CURSOR_X = 0;
    static constexpr uint8_t TRAY_B_CURSOR_X = 4;
    static constexpr uint8_t TRAY_C_CURSOR_X = 8;
    static constexpr uint8_t TRAY_D_CURSOR_X = 12;
    static constexpr uint8_t fanPower = 180;
    enum Selection: int8_t {
        NONE = 0, MINUTES, TEMPERATURE, TRAY_A, TRAY_B, TRAY_C, TRAY_D, MAX
    };
    Messaging *messaging;
    Selection selection = Selection::NONE;
    bool tickTock = true;
    bool isRunning = false;
    int8_t setMinutes = 10;
    int8_t setTemperature = 50;
    std::array<int8_t, 4> seconds = std::array<int8_t, NUMBER_OF_TRAYS>();
    std::array<int8_t, 4> minutes = std::array<int8_t, NUMBER_OF_TRAYS>();
    void updateTimers();
    void handleUserInput(UserInput *userInput);
    void handleClimateReport(ClimateReport *climateReport);
    void handleTemperatureControlStatus(TemperatureControlStatus *pStatus);
    void renderUI();
    void cycleSelection(int8_t amount);
    void changeSelected(int8_t amount);
    void renderCursor();
    void renderSetPoints();
    void renderTimers();
    void startSelectedTrayTimer();
    void renderTickTock();
    void stopDrying();
};


#endif //AVR_TIMEDMULTITRAYDRYING_H
