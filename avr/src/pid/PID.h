//
// Created by ghisi on 27.10.22.
//

#ifndef AVR_PID_H
#define AVR_PID_H


#include "cstdint"

class PID {
public:
    PID(int32_t pFactor, int32_t iFactor, int32_t dFactor);
    int32_t update(int32_t setPoint, int32_t processValue);
    void resetIntegrator();
private:
    int32_t lastProcessValue;
    int32_t sumError;
    int32_t PFactor;
    int32_t IFactor;
    int32_t DFactor;
    int32_t maxError;
    int32_t maxSumError;

    static constexpr int32_t MAX_INT = INT32_MAX;
    static constexpr int32_t MAX_LONG = INT32_MAX;
    static constexpr int32_t MAX_I_TERM = (MAX_LONG / 2);
    static constexpr uint8_t SCALING_FACTOR = 128;
};

#endif //AVR_PID_H
