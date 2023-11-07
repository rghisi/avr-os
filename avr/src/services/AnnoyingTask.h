//
// Created by ghisi on 07.11.23.
//

#ifndef AVR_ANNOYINGTASK_H
#define AVR_ANNOYINGTASK_H

class AnnoyingTask: public StaticTask<64> {
    void run() override {
        while(true) {
            auto stringBuffer = new char[1];
            sprintf_P(stringBuffer, PSTR("."));
            await(Serial::sendAsync(stringBuffer, strlen(stringBuffer)));
        }
    }
};

#endif //AVR_ANNOYINGTASK_H
