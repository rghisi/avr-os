//
// Created by ghisi on 27.10.22.
//

#include "PID.h"
#include "../system/Math.h"

PID::PID(int32_t pFactor, int32_t iFactor, int32_t dFactor,
         int32_t minControlSignal, int32_t maxControlSignal,
         int32_t maxError, int32_t maxIntegral) {
    this->sumError = 0;
    this->lastProcessValue = 0;
    this->pFactor = pFactor;
    this->iFactor = iFactor;
    this->dFactor = dFactor;
    this->minControlSignal = minControlSignal;
    this->maxControlSignal = maxControlSignal;
    this->maxError = maxError;
    this->maxIntegral = maxIntegral;
}

int32_t PID::update(int32_t setPoint, int32_t processValue) {
    auto error = setPoint - processValue;

    auto p_term = pFactor * error;

    sumError = Math::max(Math::min(sumError + error, maxIntegral), -maxIntegral);
    auto i_term = iFactor * sumError;

    auto d_term = dFactor * (lastProcessValue - processValue);

    auto ret = (p_term + i_term + d_term) >> SCALING_FACTOR;
    ret = Math::max(Math::min(ret, maxControlSignal), minControlSignal);

    lastProcessValue = processValue;

    return ret;
}

void PID::reset() {
    sumError = 0;
}
