//
// Created by ghisi on 20.11.22.
//

#ifndef AVR_EXTERNALINTERRUPTS_H
#define AVR_EXTERNALINTERRUPTS_H
class ExternalInterruptHandler {
public:
    virtual void handleExternalInterrupt() = 0;
};

class ExternalInterrupt {
public:
    virtual void setupExternalInterrupt() = 0;
    virtual void externalInterruptDisable() = 0;
    virtual void externalInterruptOnFallingEdge() = 0;
    virtual void externalInterruptOnRisingEdge() = 0;
    virtual void setExternalInterruptHandler(ExternalInterruptHandler *handler) = 0;
};
#endif //AVR_EXTERNALINTERRUPTS_H
