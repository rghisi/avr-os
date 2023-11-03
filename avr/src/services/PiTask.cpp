//
// Created by ghisi on 03.11.23.
//

#include "PiTask.h"
#include "../system/OS.h"
#include "../comms/SerialPacket.h"
#include "cstring"

void PiTask::run() {
    pi = 3.0;
    n = 2;
    sign = 1.0;
    nn = 0;
    while (true) {
        pi += sign * (4.0 / ((n) * (n + 1) * (n + 2)));
        sign = sign * (-1.0);
        n += 2;

        if (nn % 100 == 0) {
            auto stringBuffer = new char[16];
            sprintf(stringBuffer, "%.10f\n", pi);
            auto event = new SerialPacket(reinterpret_cast<uint8_t *>(stringBuffer), strlen(stringBuffer));
            OS::send(event);
            yield();
        }
        nn++;
    }
}
