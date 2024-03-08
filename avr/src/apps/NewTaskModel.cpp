//
// Created by ghisi on 08.03.24.
//

#include "NewTaskModel.h"
#include "../comms/Serial.h"
#include "cstring"

int_fast8_t NewTaskModel::main(char *args) {
    Serial::send("Wait for it...\n", 16);
    Serial::send(args, strlen(args));
    Serial::send("Bang!\n", 7);
    return 0;
}
