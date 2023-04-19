#include <string>
#include "headers/Robot.h"
using namespace std;
    

void Robot::setName(string Name) {this->Name = Name;}
string Robot::getName() {return Name;}
void Robot::setOS(string OS) {this->OS = OS;}
string Robot::getOS() {return OS;}
void Robot::setManufacture(string Manufacture) {this->Manufacture = Manufacture;}
string Robot::getManufacture() {return Manufacture;}
