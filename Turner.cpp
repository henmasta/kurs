#include "headers/Turner.h"
#include <iostream>
#include <unistd.h>  
#include <string>
#include <thread>

using namespace std;


Turner::Turner() {
    FIO = "";
    Age = 0;
    Stage = 0;
    Number = 0;
};

Turner::Turner(string FIO, int Age, int Stage, int Number) {
    this->FIO = FIO;
    this->Age = Age;
    this->Stage = Stage;
    this->Number = Number;
};
        

bool Turner::Trimming(Detail &_detail, int Size) {

    if (_detail.getName() != "" && _detail.getMetalType() != "" && _detail.getSize() != 0) {

        if (Size < _detail.getSize()) {

            _detail.setSize(Size);
            sleep(5);
            cout << "New size detail: " << Size << endl;
            return 1;
                
        } else {
            cout << "To add size you need a welder" << endl;
        }

    } else {
        throw invalid_argument("Add detail");
    }

    return 0;
}


        

void Turner::setDepartment (int Department) { this->Department = Department; }
int  Turner::getDepartament() { return Department; }

void Turner::setExperience (int Experience) { this->Experience = Experience; }
int  Turner::getExperience()  { return Experience; }

void Turner::UpExperience() {
    ++Experience;
}