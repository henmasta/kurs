#include "Employee.h"
#include "Detail.h"

class Turner : public Employee {

    private:

        int Experience;
        int Department;

        public:

            Turner() : Employee(){};
            Turner (string FIO, int Age, int Stage, int Number);
            bool Trimming(Detail &_detail, int Size);
            
            void setDepartment (int Department);
            int  getDepartament();

            void setExperience (int Experience);
            int  getExperience();

            void UpExperience();
};