#include "headers/Engine.h"
#include <iostream>
//int Engine::status_bar = 0;

Engine::Engine() {
        status_bar = 0;
}

void Engine::setStatusBar(int status_bar) {
        this->status_bar = status_bar;
        std::cout << "This is status bar -> " << getStatusBar() << endl;
}

int Engine::getStatusBar() {
        return status_bar;
}


bool Engine::Status() {
        return status_bar % 3 == 0 ? false : true;
}