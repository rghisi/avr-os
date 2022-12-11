//
// Created by ghisi on 27.10.22.
//

#ifndef AVR_PID_H
#define AVR_PID_H


#include "cstdint"

class PID {
public:
    PID(int16_t pFactor, int16_t iFactor, int16_t dFactor);
    int16_t update(int16_t setPoint, int16_t processValue);
    void resetIntegrator();
private:
    int16_t lastProcessValue;
    int32_t sumError;
    int16_t PFactor;
    int16_t IFactor;
    int16_t DFactor;
    int16_t maxError;
    int32_t maxSumError;

    static const int16_t MAX_INT = INT16_MAX;
    static const int32_t MAX_LONG = INT32_MAX;
    static const int32_t MAX_I_TERM = (MAX_LONG / 2);
    static const uint8_t SCALING_FACTOR = 128;
};

#endif //AVR_PID_H
