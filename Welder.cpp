#include <string>
#include "headers/Welder.h"
#include "headers/Employee.h"
#include "headers/Detail.h"

using namespace std;

        Welder::Welder() {};
        Welder::Welder(string FIO, int Age, int Stage, int Number, int Experience, int Departament) {
            this->FIO = FIO;
            this->Age = Age;
            this->Stage = Stage;
            this->Number = Number;
            this->Experience = Experience;
            this->Department = Departament;
        }
        
        
        
        void Welder::setDepartment (int Department) { this->Department = Department; }
        int  Welder::getDepartament() { return Department; }

        void Welder::setExperience (int Experience) { this->Experience = Experience; }
        int  Welder::getExperience()  { return Experience; }

        void Welder::UpExperience() {
            ++Experience;
        }

        bool Welder::Welding(Detail &_detail) {
            return (_detail.getName() != "" && _detail.getMetalType() != "" && _detail.getSize() != 0) ?  1 : 0;
        } 

        bool Welder::ColdWelding(Detail &_detail) {
            return (_detail.getName() != "" && _detail.getMetalType() != "" && _detail.getSize() != 0) ?  1 : 0;
        }