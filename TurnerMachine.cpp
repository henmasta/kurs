#include "headers/TurnerMachine.h"
#include "headers/Engine.h"
#include <iostream>

//bool status_en = en->Status();


/*TurnerMachine::TurnerMachine() {
    Engine* en = new Engine;
}*/

bool TurnerMachine::Power() {

    std::cout << "Hey" << endl;
	en.setStatusBar(en.getStatusBar()+1);

    //return false;
    return !en.Status() ? true : false;
}
