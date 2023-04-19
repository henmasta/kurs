#ifndef _robot_inc_h_
#define _robot_inc_h_ 

#include <string>
using namespace std;

class Robot {
    
    protected:

        string Name;
        string OS;
        string Manufacture;
    
    public:

        void setName(string Name);
        string getName();
        void setOS(string OS);
        string getOS();
        void setManufacture(string Manufacture);
        string getManufacture();

        virtual bool Power() = 0;
        virtual string Status() = 0;

};

#endif