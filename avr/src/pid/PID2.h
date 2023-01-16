//
// Created by ghisi on 1/15/23.
//

#ifndef AVR_PID2_H
#define AVR_PID2_H


#include "cstdint"
#include "../system/Math.h"

template <int32_t Kp, int32_t Ki, int32_t Kd, int32_t OutputMin, int32_t OutputMax>
class PID2 {
public:
    PID2();
    int32_t update(int32_t setPoint, int32_t processValue);
    void reset();
private:
    static constexpr double scaling = 128; //7 bits = 128
    static constexpr uint8_t scalingBits = 7; //7 bits = 128
    static constexpr int32_t dt = 1; //1s default
    static constexpr int32_t A0 = Kp + (Ki*dt);
    static constexpr int32_t A1 = -Kp;
    static constexpr int32_t A0d = Kd/dt;
    static constexpr int32_t A1d = -2 * (Kd/dt);
    static constexpr int32_t A2d = Kd/dt;
    static constexpr int32_t N = 5;
    static constexpr double tau = Kd / (double)(Kp * N);
    static constexpr double alpha = dt / (((2.0f * tau) * scaling) + (tau == 0 ? 1 : 0));
    static constexpr int32_t alpha1 = (alpha / (alpha + scaling)) * scaling;
    static constexpr int32_t alpha2 = ((alpha - scaling) / (alpha + scaling)) * scaling;

    int32_t output = 0;
    int32_t error[3]{0, 0, 0};
    int32_t d0 = 0;
    int32_t d1 = 0;
    int32_t fd0 = 0;
    int32_t fd1 = 0;

};

template<int32_t Kp, int32_t Ki, int32_t Kd, int32_t OutputMin, int32_t OutputMax>
void PID2<Kp, Ki, Kd, OutputMin, OutputMax>::reset() {
    output = 0;
}

template<int32_t Kp, int32_t Ki, int32_t Kd, int32_t OutputMin, int32_t OutputMax>
int32_t PID2<Kp, Ki, Kd, OutputMin, OutputMax>::update(int32_t setPoint, int32_t processValue) {
    error[2] = error[1];
    error[1] = error[0];
    error[0] = setPoint - processValue;
    // PI
    output = output + A0 * error[0] + A1 * error[1];
    // Filtered D
    d1 = d0;
    d0 = A0d * error[0] + A1d * error[1] + A2d * error[2];
    fd1 = fd0;
    fd0 = (alpha1 * (d0 + d1)) - (alpha2 * fd1);
    output += fd0 >> scalingBits;

    output = Math::max(Math::min(output, OutputMax), OutputMin);

    return output;
}

template<int32_t Kp, int32_t Ki, int32_t Kd, int32_t OutputMin, int32_t OutputMax>
PID2<Kp, Ki, Kd, OutputMin, OutputMax>::PID2() = default;


#endif //AVR_PID2_H
