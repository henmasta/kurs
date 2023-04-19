#include "headers/Engine.h"

bool Engine::Power() {
        power = !power;
        return power;
}
bool Engine::power = false;
