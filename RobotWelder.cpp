#include "headers/Welder.h"
#include "headers/Detail.h"
#include "headers/Robot.h"
#include "headers/RobotWelder.h"
#include <unistd.h>  
#include <iostream>
using namespace std;
    
RobotWelder::RobotWelder() {
    power = true;
    TimeWelding = 3;
};

RobotWelder::RobotWelder(int Speed, int TimeWelding, float Manipulator, float Radius) {
    this->Speed = Speed;
    this->TimeWelding = TimeWelding;
    this->Manipulator = Manipulator;
    this->Radius = Radius;
    power = true;
};

void RobotWelder::setSpeed(int Speed) {this->Speed = Speed;}
int RobotWelder::getSpeed() {return Speed;}

void RobotWelder::setTimeWelding(int TimeWelding) {this->TimeWelding = TimeWelding;}
int RobotWelder::getTimeWelding() {return TimeWelding;}

void RobotWelder::setMainpulator(float Manipulator) {this->Manipulator = Manipulator;}
float RobotWelder::getManipulator() {return Manipulator;}

void RobotWelder::setRadius(float Radius) {this->Radius = Radius;}
float RobotWelder::getRadius() {return Radius;}

bool RobotWelder::Power() {
    power = !power;
    return power;
}

bool RobotWelder::Welding(Detail &_detail, int Size) {
    
    if (power == false) {

        //cout << "OK" << endl;
        if (_detail.getName() != "" && _detail.getMetalType() != "" && _detail.getSize() != 0) {

                if (Size > _detail.getSize()) {

                    _detail.setSize(Size);
                    sleep(TimeWelding);
                    cout << "New size detail: " << Size << endl;
                    return 1;
                        
                } else {
                    cout << "To reduce the size you need a turner" << endl;
                }

            } else {
                //throw invalid_argument("Add detail");
                cout << "Add detail";
            }

    } else {
        cout << "ON ROBOT!" << endl;
    }

    return 0;
} 

float RobotWelder::Move(float corner) {return corner;}


string RobotWelder::Status() {return "";}