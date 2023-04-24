#ifndef _engine_inc_h_
#define _engine_inc_h_ 

#include <string>
using namespace std;

class Engine {

    private:
        int status_bar;
        int _Power;
        int Volume;
        string TypeEngine;

    public:

        Engine();
        
        void setStatusBar(int status_bar);
        int getStatusBar();
        bool Status();


};

#endif