#include "headers/Welder.h"
#include "headers/Detail.h"
#include "headers/Robot.h"
#include "headers/RobotWelder.h"
#include <iostream>
using namespace std;
    
RobotWelder::RobotWelder() {};
RobotWelder::RobotWelder(int Speed, int TimeWelding, float Manipulator, float Radius) {
    this->Speed = Speed;
    this->TimeWelding = TimeWelding;
    this->Manipulator = Manipulator;
    this->Radius = Radius;
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

bool RobotWelder::Welding(Detail &_detail) {
            
    if (Power()){

        cout << "OK" << endl;
        if (_detail.getName() != "" && _detail.getMetalType() != "" && _detail.getSize() != 0) {
            cout << "Detail welded!" << endl;
        }

    } else {
        cout << "ON ROBOT!" << endl;
    }

    return 0;
} 

float RobotWelder::Move(float corner) {return corner;}


string RobotWelder::Status() {return "";}
  
bool RobotWelder::power = false;
