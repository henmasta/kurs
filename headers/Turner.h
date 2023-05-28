#ifndef _turner_inc_h_
#define _turner_inc_h_ 

#include "Employee.h"
#include "Detail.h"

class Turner : public Employee {

    private:

        int Experience;
        int Departament;

        public:

            Turner();
            Turner (string FIO, int Age, int Stage, int Number);
            bool Trimming(Detail &_detail, int Size);
            
            void setDepartment (int Departament);
            int  getDepartament();

            void setExperience (int Experience);
            int  getExperience();

            void UpExperience();

            void operator++();
};

#endif