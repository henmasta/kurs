#include "headers/TurnerMachine.h"
#include "headers/Engine.h"
#include <iostream>

bool TurnerMachine::Power() {

    if (!en.Status()) {
        en.setStatusBar(en.getStatusBar()+1);
        return false;
    }
    else {
        return true;
    }
    //return en.Status() ? false : true;
}

void TurnerMachine::ToZero() {
    en.setStatusBar(1);
}