#ifndef _turner_machine_inc_h_
#define _turner_machine_inc_h_ 

#include <string>
#include "Engine.h"
using namespace std;

class TurnerMachine {
    
    private:
        Engine en;
        bool status_en;
        string Type;
        string Mode;
        string Model;

    public:
    
        //TurnerMachine();
        
        int status;
        bool Power();
        void ToZero();
};

#endif