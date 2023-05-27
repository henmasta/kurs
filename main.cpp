#include <map>
#include <dir.h>
#include <vector>
#include <thread>
#include <future>
#include <string>
#include <conio.h>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>  
#include <sys\stat.h>
#include <filesystem>

#include "headers/Employee.h"
#include "headers/Detail.h"
#include "headers/Robot.h"
#include "headers/Engine.h"
#include "headers/TurnerMachine.h"
#include "headers/Welder.h"
#include "headers/Turner.h"
#include "headers/RobotWelder.h"

#define MAX 100

using namespace std;
using namespace filesystem;


vector<Turner> push_from_file_turner(vector<Turner> trn, string file) {
    
    
    string file_line;

    int NO;
    string FIO  ;
    int    Age  ;
    int    Stage;
    int   Number;
    
    ifstream turner_file(file);

    if(!turner_file && !exists(file)) {
        cout << "error open file " << file << endl;
        ofstream (file);
        return trn;
    }
    
    while (!turner_file.eof()){
        turner_file >> NO;
        turner_file >> FIO;
        turner_file >> Age;
        turner_file >> Stage;
        turner_file >> Number;

        Turner turner(FIO, Age, Stage, Number);
        trn.push_back(turner);
    }

    return trn;
     
}

void read_from_file(string file) {

    string file_line;

    ifstream in(file);

    if (in.is_open()) 
        while (getline(in, file_line))
            cout << file_line << endl;
    
    in.close();
}

int last_line(const string filename) {

    string str =  "";
    int n = 0;

    ifstream inClientFile(filename, ios::in);
 
    if (!inClientFile) {
        cerr << "File could not be opened" << endl;
        exit(1);
    }
 
    string buf;
 
    while (getline(inClientFile, buf))
        n++;
    
    if (n < 1) return n+1;
    return n;
}
/*
1 pet 22 2 153
2 gg 12 4 152
*/

int main () {


    int size, n, det, i = 0;
    bool language = true;
    string path_to_lang = "interface/isp/";
    string turner_data = "database/turners";
    
    vector <Turner> turners;
    vector <TurnerMachine> mach;
    vector <Detail> details;
    vector <Welder> welders;
    vector <RobotWelder> robot_welders;


    string FIO  ;
    int    Age  ;
    int    Stage;
    int   Number;
    int Experience;
    int Departament;

    int Size;
    string Name;
    string MetalType;

    int Speed;
    int TimeWelding;
    float Manipulator;
    float Radius;
    ofstream out;

    TurnerMachine turn;
    Engine eng;

    map <int, string> turners_number;
    
    
    int choice, choice2, choice3;
    
    //Turner turner("pety", 22, 2, 153);
    //Detail dett(20, "detail1", "fe");
    //turners.push_back(turner);
    //details.push_back(dett);


    //path folderPath("database");

    ofstream f("database/turners.txt");

    f << "";
    f.close();

    /*if (!exists(folderPath) && 
        !is_directory(folderPath)
    ) {
        //mkdir("database");
        ofstream ("database/turners.txt");
        ofstream ("database/welders.txt");
        ofstream ("database/robot_welders.txt");
    }*/




    turners = push_from_file_turner(turners, "database/turners.txt");

    do {

        //system("cls");
        if(language)
            path_to_lang = "interface/eng/";
        else 
            path_to_lang = "interface/isp/";
        
        read_from_file(path_to_lang + "menu.txt");
        

        choice = getch();
        
        //system("cls");
        if (choice == 9)  {

            language = !language;
            
            cout << "Language replaced" << endl;
        }
        
        if (choice == '1') {

            read_from_file(path_to_lang + "turner_main_menu.txt");
            
            choice2 = getch();

            if (choice2 == '1') {

                cout << "FIO \t Age \t Stage \t Number" << endl;
                cin >> FIO >> Age >> Stage >> Number;

                turners_number[Number] = to_string(last_line("database/turners.txt")) + "." + " FIO: " + FIO + " Age: " + to_string(Age) + " Stage: " + to_string(Stage) + " Number: " + to_string(Number);
                Turner turner(FIO, Age, Stage, Number);            
                
                turners.push_back(turner);
                cout << "OK" << endl;
            }

            if (choice2 == '2') {
                i = 0;
                cout << "Turners: " << endl;
                cout << "NO \t FIO \t Age \t Stage \t Number" << endl;

                for(Turner t : turners) 
                    cout << to_string(++i) + ". " + t.getFIO() << " \t " << 
                                                    t.getAge() << " \t " << 
                                                    t.getStage() << " \t " << 
                                                    t.getNumber() << endl;
            }

            if (choice2 == '3') {
                if (!turn.Power()) {
                    //cout << eng.getStatusBar() << endl;
                    if (!turners.empty()) {

                        i = 0;
                        
                        if (language)
                            cout << "Who make it's work? " << endl;
                        else
                            cout << "Quien hace que funcione? " << endl;
                        
                        for(Turner t : turners) 
                            cout << to_string(++i) + ". " + t.getFIO() << " \t " << 
                                                            t.getAge() << " \t " << 
                                                            t.getStage() << " \t " << 
                                                            t.getNumber() << endl;
                        do {
                            if (language)
                                cout << "Enter tuner number: ";
                            else
                                cout << "Introduzca el numero de sintonizador: ";

                            cin >> n;
                        } while(n < 0 || n > i);
                    

                        if (!details.empty()) {
                            i = 0;
                            for(Detail d : details) 
                                cout << to_string(++i) + ". " + to_string(d.getSize()) << " \t " << 
                                                                        d.getName() << " \t " << 
                                                                        d.getMetalType() << endl;
                            do {

                                if (language)
                                    cout << "Enter number detail: ";
                                else
                                    cout << "Ingrese el detalle del numero: ";

                                cin >> det;

                                if (det > i || det < 0) 
                                    if (language)
                                        cout << "Enter exactly number!" << endl;
                                    else 
                                        cout << "Ingrese el numero exacto!" << endl;
                                                
                            } while (det > i || det < 0);

                            do {

                                cout << "Enter size detail: ";
                                cin >> size;
                                if (size < 0 || size > details.at(det-1).getSize()) cout << "Enter exactly size!" << endl;

                            } while(size < 0 || size > details.at(det-1).getSize());
                        } else {
                            cout << "Add minimum 1 detail" << endl;
                        }
                    } else {
                        cout << "Add minimum 1 turner" << endl;
                    }
                    

                    if (!turners.empty() && !details.empty()) 
                        turners.at(n-1).Trimming(details.at(det-1), size);

                } else {
                    cout << "Crash";
                }
            }

            if (choice2 == '4') {
                turn.ToZero();
            }
            
            if (choice2 == '5') {

                i = 0;

                cout << "FIO \t Age \t Stage \t Number" << endl;

                for(Turner t : turners) 
                    cout << to_string(++i) + ". " + t.getFIO() << " \t " << 
                                                    t.getAge() << " \t " << 
                                                    t.getStage() << " \t " << 
                                                    t.getNumber() << endl;


                cout << "Enter Number for delete Turner: ";
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

        }

        if (choice == '2') {
            cout << "1. Add Welder\n" <<
                    "2. Output welders list\n" <<
                    "3. Welding detail\n" <<
                    "4. Del Welder\n" << 
                    "Esc. Exit" << endl;
            
            choice2 = getch();

            if (choice2 == '1') {

                cout << "FIO \t Age \t Stage \t Number \t Experience \t Departament" << endl;
                cin >> FIO >> Age >> Stage >> Number >> Experience >> Departament;

                Welder welder(FIO, Age, Stage, Number, Experience, Departament);            
            
                welders.push_back(welder);
                cout << "OK" << endl;

            }

            if (choice2 == '2') {
                i = 0;
                cout << "Welders: " << endl;
                cout << "FIO \t Age \t Stage \t Number \t Experience \t Departament" << endl;

                for(Welder w : welders) 
                    cout << to_string(++i) + ". " + w.getFIO() << " \t " << 
                                                    w.getAge() << " \t " << 
                                                    w.getStage() << " \t " << 
                                                    w.getNumber() << " \t " << 
                                                    w.getExperience() << " \t " << 
                                                    w.getDepartament() << endl;
            }

            if (choice2 == '3') {

                if (!welders.empty()) {

                    i = 0;
                    cout << "Who make it's work? " << endl;

                    cout << "FIO \t Age \t Stage \t Number \t Experience \t Departament" << endl;

                    for(Welder w : welders) 
                        cout << to_string(++i) + ". " + w.getFIO() << " \t " << 
                                                        w.getAge() << " \t " << 
                                                        w.getStage() << " \t " << 
                                                        w.getNumber() << " \t " << 
                                                        w.getExperience() << " \t " << 
                                                        w.getDepartament() << endl;
                    do {
                        cout << "Enter welder number: ";
                        cin >> n;
                    } while(n < 0 || n > i);
                

                    if (!details.empty()) {
                        i = 0;
                        for(Detail d : details) 
                            cout << to_string(++i) + ". " + to_string(d.getSize()) << " \t " << 
                                                                    d.getName() << " \t " << 
                                                                    d.getMetalType() << endl;
                        do {

                            cout << "Enter number detail: ";
                            cin >> det;
                            if (det > i || det < 0) cout << "Enter exactly number!" << endl;
                                            
                        } while (det > i || det < 0);

                        do {

                            cout << "Enter size detail: ";
                            cin >> size;
                            if (size < 0 || size < details.at(det-1).getSize()) cout << "Enter exactly size!" << endl;

                        } while(size < 0 || size < details.at(det-1).getSize());
                    } else {
                        cout << "Add minimum 1 detail" << endl;
                    }
                } else {
                    cout << "Add minimum 1 welder" << endl;
                }
                

                if (!welders.empty() && !details.empty()) 
                    welders.at(n-1).Welding(details.at(det-1), size);
            }

            if (choice2 == '4') {

                i = 0;

                cout << "FIO \t Age \t Stage \t Number" << endl;

                for(Welder w : welders) 
                    cout << to_string(++i) + ". " + w.getFIO() << " \t " << 
                                                    w.getAge() << " \t " << 
                                                    w.getStage() << " \t " << 
                                                    w.getNumber() << " \t " << 
                                                    w.getExperience() << " \t " << 
                                                    w.getDepartament() << endl;


                cout << "Enter Number for delete Welder: ";
                cin >> n;

                if (i >= n) {

                    cout << "Elemet " << welders.at(n-1).getFIO() << " \t " 
                                      << welders.at(n-1).getAge() << " \t " 
                                      << welders.at(n-1).getStage() << " \t " 
                                      << welders.at(n-1).getNumber() 
                                      << " Delete!" << endl;

                    welders.erase(welders.begin() + n-1);
                } else 
                    cout << "Not exists!" << endl;
            }
        }

        if (choice == '3') {

            cout << "1. Add Robot Welder\n" <<
                    "2. Output robot welders list\n" <<
                    "3. Welding detail\n" <<
                    "4. On robot\n" <<
                    "5. Del Robot Welder\n" << 
                    "Esc. Exit" << endl;
            
            choice2 = getch();

            if (choice2 == '1') {
                cout << "NO \t Speed \t Time Welding \t Manipulator \t Radius" << endl;

                do {
                    cin >> Speed >> TimeWelding >> Manipulator >> Radius;
                    fflush(stdin);
                } while (Speed < 0 || 
                        TimeWelding < 0 || 
                        Manipulator < 0 || 
                        Radius < 0);

                RobotWelder robot_welder(Speed, TimeWelding, Manipulator, Radius);            
            
                robot_welders.push_back(robot_welder);
                cout << "OK" << endl;   
            }

            if (choice2 == '2') {
                i = 0;

                cout << "Robot Welders:" << endl;
                cout << "Speed \t Time Welding \t Manipulator \t Radius" << endl;

                for (RobotWelder r : robot_welders) 
                    cout << to_string(++i) + ". " + to_string(r.getSpeed()) << "\t"
                         << r.getTimeWelding() << "\t"
                         << r.getManipulator() << "\t"
                         << r.getRadius()
                    << endl;
            }

            if (choice2 == '3') {
                if (!robot_welders.empty()) {

                    i = 0;
                    cout << "Who make it's work? " << endl;

                    cout << "FIO \t Age \t Stage \t Number \t Experience \t Departament" << endl;

                    for(RobotWelder r : robot_welders) 
                        cout << to_string(++i) + ". " + to_string(r.getSpeed()) << "\t"
                            << r.getTimeWelding() << "\t"
                            << r.getManipulator() << "\t"
                            << r.getRadius()
                        << endl;
                    
                    do {
                        cout << "Enter robot welder number: ";
                        cin >> n;
                    } while(n < 0 || n > i);
                

                    if (!details.empty()) {
                        i = 0;
                        for(Detail d : details) 
                            cout << to_string(++i) + ". " + to_string(d.getSize()) << " \t " << 
                                                                    d.getName() << " \t " << 
                                                                    d.getMetalType() << endl;
                        do {

                            cout << "Enter number detail: ";
                            cin >> det;
                            if (det > i || det < 0) cout << "Enter exactly number!" << endl;
                                            
                        } while (det > i || det < 0);

                        do {

                            cout << "Enter size detail: ";
                            cin >> size;
                            if (size < 0 || size < details.at(det-1).getSize()) 
                                cout << "Enter exactly size!" << endl;

                        } while(size < 0 || size < details.at(det-1).getSize());

                    } else {
                        cout << "Add minimum 1 detail" << endl;
                    }
                } else {
                    cout << "Add minimum 1 welder" << endl;
                }
                

                if (!robot_welders.empty() && !details.empty()) 
                    robot_welders.at(n-1).Welding(details.at(det-1), size);
            }

            if (choice2 == '4') {
                cout << "Number robot for on/off: ";
                do {
                    cin >> n;
                } while(n < 0 || n > i);
                robot_welders.at(n-1).Power();
            }


        }

        if (choice == '4') {

            cout << "1. Add detail\n" <<
                    "2. Output delail list\n" <<
                    "3. Del detail\n" <<
                    "Esc. Exit" << endl;

            choice2 = getch();

            if (choice2 == '1') {
                cout << "Size \t Name \t Metal Type" << endl;
                cin >> Size >> Name >> MetalType;

                Detail detail(Size, Name, MetalType);            
                
                details.push_back(detail);
                cout << "OK" << endl;
            }


            if (choice2 == '2') {
                
                i = 0;

                if (!details.empty()) {
                    for(Detail d : details) 
                        cout << to_string(++i) + ". " + to_string(d.getSize()) << " \t " << 
                                                                d.getName() << " \t " << 
                                                                d.getMetalType() << endl; 
                } else {
                    cout << "Add minimum 1 detail" << endl;
                }   
            }

            if (choice2 == '3') {
                
                i = 0;

                if (!details.empty()) {
                    cout << "Details: " << endl;
                    for(Detail d : details) 
                        cout << to_string(++i) + ". " + to_string(d.getSize()) << " \t " << 
                                                                d.getName() << " \t " << 
                                                                d.getMetalType() << endl; 
                    do {
                        cout << "Number detail for delete: ";
                        cin >> n;
                    } while(n < 0 || n > i);
                    cout << "Detail with name " << details.at(n-1).getName() << " delete" << endl;

                    details.erase(details.begin() + n-1);
                } else {
                    cout << "Add minimum 1 detail" << endl;
                }   
            }
        }


        if (choice == 48) {
            break;
        }
        getch();

    } while((choice != 48));

    cout << "goodbye" << endl;

    i = 0;
    out.open("database/turners.txt");
    if (out.is_open())
        if(last_line("database/turners.txt") != 1)
            for (Turner t : turners)
                out << to_string(++i) + " " + t.getFIO() + " " + to_string(t.getAge()) + " " + to_string(t.getStage()) + " " + to_string(t.getNumber());
        else {
            for (Turner t : turners)
                out <<"\n" + to_string(++i) + " " + t.getFIO() + " " + to_string(t.getAge()) + " " + to_string(t.getStage()) + " " + to_string(t.getNumber());
        }
    cout << "OK" << endl;
    out.close();

    return 0;
}
