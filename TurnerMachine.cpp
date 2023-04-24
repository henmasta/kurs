#include "headers/TurnerMachine.h"
#include "headers/Engine.h"
#include <iostream>

//bool status_en = en->Status();


TurnerMachine::TurnerMachine() {
    Engine* en = new Engine;
}

bool TurnerMachine::Power() {

    std::cout << "Hey" << endl;
	en->setStatusBar(1);

    return !en->getStatusBar() ? true : false;
}
