//
// Created by ghisi on 1/2/23.
//

#ifndef AVR_APPLICATION_H
#define AVR_APPLICATION_H


class Application {
public:
    virtual void toForeground();
    virtual void toBackground();

protected:
    enum class RunningState {
        FOREGROUND,
        BACKGROUND
    };
    RunningState runningState = RunningState::BACKGROUND;
};


#endif //AVR_APPLICATION_H
