//
// Created by ghisi on 1/2/23.
//

#ifndef AVR_APPLICATION_H
#define AVR_APPLICATION_H


class Application {
public:
    virtual char* title() = 0;
    virtual void toForeground();
    virtual void toBackground();
    bool isRunning();

protected:
    enum class RunningState {
        FOREGROUND,
        BACKGROUND,
        RUNNING
    };

    RunningState runningState = RunningState::BACKGROUND;
};


#endif //AVR_APPLICATION_H
