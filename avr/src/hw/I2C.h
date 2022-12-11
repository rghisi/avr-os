//
// Created by ghisi on 10.11.22.
//

#ifndef AVR_I2C_H
#define AVR_I2C_H

#include "cstdint"

class I2CInterruptHandler {
public:
    virtual void handleI2CInterrupt() = 0;
};

class I2C {
public:
    virtual uint8_t sendI2C(void *const data, uint8_t length, uint8_t repStart) = 0;
    virtual uint8_t receiveI2C(uint8_t address, uint8_t bytesToRead, uint8_t repStart) = 0;
    virtual void setInterruptHandler(I2CInterruptHandler *handler) = 0;
};

#endif //AVR_I2C_H
