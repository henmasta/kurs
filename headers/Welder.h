#ifndef _welder_inc_h_
#define _welder_inc_h_ 

#include <string>
#include "Employee.h"
#include "Detail.h"
using namespace std;

class Welder : public Employee {
    
    private:

        int Experience;
        int Department;

    public:

        Welder();
        Welder(string FIO, int Age, int Stage, int Number, int Experience, int Departament);
        
        void setDepartment (int Department);
        int  getDepartament();

        void setExperience (int Experience);
        int  getExperience();

        void operator++();

        bool Welding(Detail &_detail, int Size);

        bool ColdWelding(Detail &_detail);

        virtual string companyName();
};

#endif