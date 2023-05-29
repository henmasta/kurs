#ifndef _robot_welder_inc_h_
#define _robot_welder_inc_h_ 

#include "Robot.h"
#include "Welder.h"
#include "Detail.h"

class RobotWelder : public Robot, public Welder {

    private:
        bool power;
        int Speed;
        int TimeWelding;
        float Manipulator;
        float Radius;
        float Move_num;

    public:

        RobotWelder();
        RobotWelder(int Speed, int TimeWelding, float Manipulator, float Radius);


        void setSpeed(int Speed);
        int getSpeed();

        void setTimeWelding(int TimeWelding);
        int getTimeWelding();

        void setMainpulator(float Manipulator);
        float getManipulator();

        void setRadius(float Radius);
        float getRadius();

        bool Power();
        bool Welding(Detail &_detail, int Size);

        void Move(float Move_num);


        string Status();
};  

#endif