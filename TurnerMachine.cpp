#include "headers/TurnerMachine.h"

bool TurnerMachine::Power() {
        power = !power;
        return power;
}
bool TurnerMachine::power = false;
