#include <map>
#include <vector>
#include <thread>
#include <string>
#include <conio.h>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>  
#include "headers/Employee.h"
#include "headers/Detail.h"
#include "headers/Turner.h"
#define MAX 100

using namespace std;




class Engine {

    private:
        static bool power;
        int _Power;
        int Volume;
        string TypeEngine;

    public:
        bool Power() {
            power = !power;
            return power;
        }
    
};
bool Engine::power = false;

class TurnerMachine {
    
    
    private:
        static bool power;
        string Type;
        string Mode;
        string Model;

    public:

        bool Power() {
            power = !power;
            return power;
        }
};

bool TurnerMachine::power = false;


class Welder : public Employee {

    private:

        int Experience;
        int Department;

    public:

        Welder() {};
        Welder(string FIO, int Age, int Stage, int Number, int Experience, int Departament) {
            this->FIO = FIO;
            this->Age = Age;
            this->Stage = Stage;
            this->Number = Number;
            this->Experience = Experience;
            this->Department = Departament;
        };
        
        
        
        void setDepartment (int Department) { this->Department = Department; }
        int  getDepartament() { return Department; }

        void setExperience (int Experience) { this->Experience = Experience; }
        int  getExperience()  { return Experience; }

        void UpExperience() {
            ++Experience;
        }

        bool Welding(Detail &_detail) {
            return (_detail.getName() != "" && _detail.getMetalType() != "" && _detail.getSize() != 0) ?  1 : 0;
        } 

        bool ColdWelding(Detail &_detail) {
            return (_detail.getName() != "" && _detail.getMetalType() != "" && _detail.getSize() != 0) ?  1 : 0;
        }
};


class Robot {
    
    protected:

        string Name;
        string OS;
        string Manufacture;
    
    public:

        void setName(string Name) {this->Name = Name;}
        string getName() {return Name;}
        void setOS(string OS) {this->OS = OS;}
        string getOS() {return OS;}
        void setManufacture(string Manufacture) {this->Manufacture = Manufacture;}
        string getManufacture() {return Manufacture;}

        virtual bool Power() = 0;
        virtual string Status() = 0;

};

class RobotWelder : public Robot, public Welder {

    

    private:
        static bool power;
        int Speed;
        int TimeWelding;
        float Manipulator;
        float Radius;

    public:

        RobotWelder() {};
        RobotWelder(int Speed, int TimeWelding, float Manipulator, float Radius) {
            this->Speed = Speed;
            this->TimeWelding = TimeWelding;
            this->Manipulator = Manipulator;
            this->Radius = Radius;
        };
        ~RobotWelder(){};


        void setSpeed(int Speed) {this->Speed = Speed;}
        int getSpeed() {return Speed;}

        void setTimeWelding(int TimeWelding) {this->TimeWelding = TimeWelding;}
        int getTimeWelding() {return TimeWelding;}

        void setMainpulator(float Manipulator) {this->Manipulator = Manipulator;}
        float getManipulator() {return Manipulator;}

        void setRadius(float Radius) {this->Radius = Radius;}
        float getRadius() {return Radius;}

        bool Power() {
            power = !power;
            return power;
        }

        bool Welding(Detail &_detail) {
            
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

        float Move(float corner) {return corner;}


        string Status() {return "";}
};  

bool RobotWelder::power = false;

int main () {

    int size, n, i = 0;

    string FIO  ;
    int   Age   ;
    int   Stage ;
    int   Number;
    int Experience;
    int Departament;

    int Speed;
    int TimeWelding;
    float Manipulator;
    float Radius;

    map<int, string> turners_number;
    vector<Turner> turners;
    TurnerMachine mach;
    Detail detail;
    Welder weld;
    RobotWelder rob;
    
    int choice, choice2;

    
    
    do {

        system("cls");

        cout << "1. Add Turner\n" <<
                "2. Add Welder\n" <<
                "3. Add Robot Welder\n" <<
                "4. Add Detail\n" <<
                "5. Output Turner\n" <<
                "6. Output Welder\n" <<
                "7. Turner\n"<<
                "8. Welder\n" <<
                "9. Del Turner\n" <<
                "ESC. Exit" << endl;

        choice = getch();

        //по стандарту C++ 6.7 нельзя обходить объявление инциализации
        //если кратко switch нельзя

        if (choice == '1') {
            cout << "FIO \t Age \t Stage \t Number" << endl;
            cin >> FIO >> Age >> Stage >> Number;

            turners_number[Number] = to_string(i+1) + " FIO: " + FIO + " Age: " + to_string(Age) + " Stage: " + to_string(Stage) + " Number: " + to_string(Number);
            Turner turner(FIO, Age, Stage, Number);

            //cout << "\nFIO \t Age \t Stage \t Number" << endl;
            //cout << turner.getFIO() << " \t " << turner.getAge() << " \t " << turner.getStage() << " \t " << turner.getNumber() << endl;
            
            
            turners.push_back(turner);
            cout << "OK" << endl;
            //cout << "Number: " + turners_number[153] << endl;
        }

        if (choice == '2') {

            cout << "FIO \t Age \t Stage \t Number" << endl;
            cin >> FIO >> Age >> Stage >> Number >> Experience >> Departament;
            //turners[Number] = FIO;
            Welder welder(FIO, Age, Stage, Number, Experience, Departament);

            cout << "FIO \t Age \t Stage \t Number \t Experience \t Departament" << endl;
            cout << welder.getFIO() << " \t " << 
                    welder.getAge() << " \t " <<
                    welder.getStage() << " \t " << 
                    welder.getNumber() << " \t " << 
                    welder.getExperience() << " \t " << 
                    welder.getDepartament() << endl;
        }

        if (choice == '3') {
            cout << "Speed \t Time Welding \t Manipulator \t Radius" << endl;
            cin >> Speed >> TimeWelding >> Manipulator >> Radius;
            RobotWelder robot_welder(Speed, TimeWelding, Manipulator, Radius);
        }

        if (choice == '4') {
            i = 0;
            for(Turner t : turners) 
                cout << to_string(++i) + ". " + t.getFIO() << " \t " << 
                                                t.getAge() << " \t " << 
                                                t.getStage() << " \t " << 
                                                t.getNumber() << endl;
        }

        if (choice == '6') {
            system("cls");

            cout << "1. Trimming\n" << 
                    "2. Exit" << endl;

            choice2 = getch();

            if (choice2 == '1') {

                i = 0;
                cout << "Who make it's work? " << endl;
                
                for(Turner t : turners) 
                    cout << to_string(++i) + ". " + t.getFIO() << " \t " << 
                                                    t.getAge() << " \t " << 
                                                    t.getStage() << " \t " << 
                                                    t.getNumber() << endl;
                cin >> n;

                cout << "Enter size detail: ";
                cin >> size;

                try {
                    turners.at(n-1).Trimming(detail, size);
                } catch (const invalid_argument& err) {
                    //create detail

                    //деталей же тоже несколько может быть...
                    cout << "Detail not created!" << endl;
                }
            }
        }


        if (choice == '8') {

            cout << "Enter Number: " << endl;
            cin >> n;

            if (i >= n) {

                cout << "Elemet " << turners.at(n-1).getFIO() << " \t " 
                                  << turners.at(n-1).getAge() << " \t " 
                                  << turners.at(n-1).getStage() << " \t " 
                                  << turners.at(n-1).getNumber() 
                                  << " Delete!" << endl;

                turners.erase(turners.begin() + n-1);
            } else 
                cout << "Not exists!" << endl;
        }
                   
        getch();

    } while(choice != 27);
    
/*
petya 22 2 153

gay 35 5 12

natural 5 8 12
*/
    //weld.setAge(22);

    //turner.Trimming(detail, 13);
    //rob.Power();
    //rob.Power();
    //!rob.Power() ? cout << "ON\n" : cout << "OFF\n";
    
    //rob.Welding(detail);

    return 0;
}
