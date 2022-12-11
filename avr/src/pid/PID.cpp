//
// Created by ghisi on 27.10.22.
//

#include "PID.h"

PID::PID(int16_t pFactor, int16_t iFactor, int16_t dFactor) {
    // Start values for PID controller
    sumError = 0;
    lastProcessValue = 0;
    // Tuning constants for PID loop
    PFactor = pFactor;
    IFactor = iFactor;
    DFactor = dFactor;
    // Limits to avoid overflow
    maxError = MAX_INT / (PFactor + 1);
    maxSumError = MAX_I_TERM / (IFactor + 1);
}

int16_t PID::update(int16_t setPoint, int16_t processValue) {
    int16_t error, p_term, d_term;
    int32_t i_term, ret, temp;

    error = setPoint - processValue;

    // Calculate Pterm and limit error overflow
    if (error > maxError) {
        p_term = MAX_INT;
    } else if (error < -maxError) {
        p_term = -MAX_INT;
    } else {
        p_term = PFactor * error;
    }

    // Calculate Iterm and limit integral runaway
    temp = sumError + error;
    if (temp > maxSumError) {
        i_term = MAX_I_TERM;
        sumError = maxSumError;
    } else if (temp < -maxSumError) {
        i_term = -MAX_I_TERM;
        sumError = -maxSumError;
    } else {
        sumError = temp;
        i_term = IFactor * sumError;
    }

    // Calculate Dterm
    d_term = DFactor * (lastProcessValue - processValue);

    lastProcessValue = processValue;

    ret = (p_term + i_term + d_term) / SCALING_FACTOR;
    if (ret > MAX_INT) {
        ret = MAX_INT;
    } else if (ret < -MAX_INT) {
        ret = -MAX_INT;
    }

    return ((int16_t) ret);
}

void PID::resetIntegrator() {
    sumError = 0;
}
