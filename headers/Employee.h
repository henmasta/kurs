#ifndef _employee_inc_h_
#define _employee_inc_h_ 

#include <string>
using namespace std;

class Employee {

    protected:
        string FIO  ;
        int   Number;
        int   Age   ;
        int   Stage ;

    public:
    
        void setFIO(string FIO);
        string getFIO();

        void setNumber(int Number);
        int getNumber();

        void setAge(int Age);
        int getAge();

        void setStage(int Stage);
        int getStage();

        virtual string companyName() = 0;

};

#endif

