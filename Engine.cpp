#include "headers/Engine.h"
#include <iostream>

Engine::Engine() {
        status_bar = 1;
}

void Engine::setStatusBar(int status_bar) {
        this->status_bar = status_bar;
}

int Engine::getStatusBar() {
        return status_bar;
}


bool Engine::Status() {
        return status_bar % 4 == 0 ? true : false;
}