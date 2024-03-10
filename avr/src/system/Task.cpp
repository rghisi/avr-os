//
// Created by ghisi on 09.03.24.
//

#include "Task.h"

Task::Task() {
    this->stack = new StaticStack<96>();
}

Task::~Task() {
    delete stack;
}