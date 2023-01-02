//
// Created by ghisi on 1/2/23.
//

#ifndef AVR_APPLICATION_H
#define AVR_APPLICATION_H


class Application {
public:
    virtual void stop();

    virtual void toForeground();

    virtual void toBackground();
    virtual void renderUI() = 0;
protected:
    enum class RunningState {
        RUNNING_FOREGROUND,
        RUNNING_BACKGROUND,
        STOPPED
    };
    RunningState runningState = RunningState::STOPPED;
};


#endif //AVR_APPLICATION_H
