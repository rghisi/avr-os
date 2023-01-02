//
// Created by ghisi on 1/2/23.
//

#include "DisableCursor.h"

void DisableCursor::command(Display *display) {
    display->disableCursor();
}
