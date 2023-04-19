#include <string>
using namespace std;

class Employee {

    protected:
        string FIO  ;
        int   Number;
        int   Age   ;
        int   Stage ;

    public:
    
        Employee();
        void setFIO(string FIO);
        string getFIO();

        void setNumber(int Number);
        int getNumber();

        void setAge(int Age);
        int getAge();

        void setStage(int Stage);
        int getStage();

};