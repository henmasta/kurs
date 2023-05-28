#include <map>
#include <dir.h>
#include <regex>
#include <vector>
//#include <future>
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

vector<Turner> push_from_file_turner(vector<Turner> trn, string file) {
    
    int NO;
    string FIO  ;
    int    Age  ;
    int    Stage;
    int   Number;

    if (last_line(file) <= 1) return trn;
    
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

vector<Welder> push_from_file_welder(vector<Welder> wld, string file) {
    
    int NO;
    string FIO  ;
    int    Age  ;
    int    Stage;
    int   Number;
    int Experience;
    int Departament;


    if (last_line(file) <= 1) return wld;
    
    ifstream welder_file(file);

    if(!welder_file && !exists(file)) {
        cout << "error open file " << file << endl;
        ofstream (file);
        return wld;
    }
    
    while (!welder_file.eof()){
        welder_file >> NO;
        welder_file >> FIO;
        welder_file >> Age;
        welder_file >> Stage;
        welder_file >> Number;
        welder_file >> Experience;
        welder_file >> Departament;

        Welder welder(FIO, Age, Stage, Number, Experience, Departament);
        wld.push_back(welder);
    }

    return wld;


}

/*
vector<RobotWelder> push_from_file_robot_welder(vector<RobotWelder> rbt, string file) {
    
    int NO;
    int Speed;
    int TimeWelding;
    float Manipulator;
    float Radius;

    if (last_line(file) <= 1) return rbt;
    
    ifstream robot_welder_file(file);

    if(!robot_welder_file && !exists(file)) {
        cout << "error open file " << file << endl;
        ofstream (file);
        return rbt;
    }
    
    while (!robot_welder_file.eof()){
        robot_welder_file >> NO;
        

        RobotWelder robot_welder(FIO, Age, Stage, Number, Experience, Departament);
        rbt.push_back(welder);
    }

    return rbt;




}
*/

void read_from_file(string file) {

    string file_line;

    ifstream in(file);

    if (in.is_open()) 
        while (getline(in, file_line))
            cout << file_line << endl;
    
    in.close();
}

string path_folders;
string file_path_name;

void slice_user_path(string path) {

    string path_b;
    int count = 0;
    
    for (int i = path.length(); i >= 0; i--) {
        
        path_b = path[i];
        
        if (path_b.compare("/") == 0) {
            count = i;
            break;
        }
    }
    
    
    
    for(int i = 0; i <= count; i++) {
        path_folders += path[i];
    }
    
    for (int i = count+1; i < path.length(); i++) {
        file_path_name += path[i];
    }
}

void set_path_to_database(string user_database_path, string first, string standart_path, ofstream& out) {
    
    if (!exists(user_database_path)) {
        if(first.compare("0")) {
            
            slice_user_path(user_database_path);

            char* path_folders_to_char = new char[path_folders.length() + 1];
            strcpy(path_folders_to_char, path_folders.c_str());

            try {

                mkdir(path_folders_to_char);
                if (!exists(path_folders) || regex_match(path_folders, regex("[A-Za-z0-9 ]"))) 
                    throw "not created";
            } catch (...){
                cerr << "path not created" << endl;
                exit(-1);
            }
            delete(path_folders_to_char);
            out.open(user_database_path);
            out.close();
        } else {
            user_database_path = standart_path;

            if(!exists(user_database_path)){

                slice_user_path(user_database_path);
                char* path_folders_to_char = new char[path_folders.length() + 1];
                strcpy(path_folders_to_char, path_folders.c_str());

                mkdir(path_folders_to_char);
                
                delete(path_folders_to_char);

                path_folders = "";
                file_path_name = "";

                out.open(user_database_path);
                out.close();
            }
        }      
    } 
}

int main () {


    int size, n, det, i = 0;
    bool language = true;
    string path_to_lang;
    
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

    string user_database_path_turners,
            user_database_path_welders,
            user_database_path_robot_welders;

    string first_turner, first_welder, first_robot_welder;
    

    system("cls");

    cout << "Enter path for turners to database(for standart path \"database/turners.txt\" type 0): ";
    cin >> user_database_path_turners;
    first_turner = user_database_path_turners[0]; 

    cout << "Enter path for welders to database(for standart path \"database/welders.txt\" type 0): ";
    cin >> user_database_path_welders;
    first_welder = user_database_path_welders[0];

    cout << "Enter path for robot welders to database(for standart path \"database/robot_welders.txt\" type 0): ";
    cin >> user_database_path_robot_welders;
    first_robot_welder = user_database_path_robot_welders[0];
    

    set_path_to_database(user_database_path_turners, first_turner, "database/turners.txt", out);  
    set_path_to_database(user_database_path_welders, first_welder, "database/welders.txt", out);  
    set_path_to_database(user_database_path_robot_welders, first_robot_welder, "database/robot_welders.txt", out);    

    if(!first_turner.compare("0"))
        user_database_path_turners = "database/turners.txt";
    
    if(!first_welder.compare("0"))
        user_database_path_welders = "database/welders.txt";

    if(!first_robot_welder.compare("0"))
        user_database_path_robot_welders = "database/robot_welders.txt";

    if (exists(user_database_path_turners)) {
        turners = push_from_file_turner(turners, user_database_path_turners);
    }

    if (exists(user_database_path_welders)) {
        welders = push_from_file_welder(welders, user_database_path_welders);
    }

    //if (exists(user_database_path_robot_welders)) {
    //    robot_welders = push_from_file_robot_welder(robot_welders, user_database_path_robot_welders);
    //}

    do {

        system("cls");
        if(language)
            path_to_lang = "interface/eng/";
        else 
            path_to_lang = "interface/isp/";
        
        read_from_file(path_to_lang + "menu.txt");
        

        choice = getch();
        
        system("cls");
        if (choice == 9)  {
            if (language)
                cout << "Language replaced" << endl;
            else 
                cout << "Idioma reemplazado" << endl;
            language = !language;
            
        }
        
        if (choice == '1') {

            read_from_file(path_to_lang + "turner_main_menu.txt");
            
            choice2 = getch();

            if (choice2 == '1') {

                cout << "FIO \t Age \t Stage \t Number" << endl;
                cin >> FIO >> Age >> Stage >> Number;

                //turners_number[Number] = to_string(last_line("database/turners.txt")) + "." + " FIO: " + FIO + " Age: " + to_string(Age) + " Stage: " + to_string(Stage) + " Number: " + to_string(Number);
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
                                
                                if (size < 0 || size > details.at(det-1).getSize()) 
                                    cout << "Enter exactly size!" << endl;

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

                    language ? cout << "Not exists!" << endl : cout << "No existe!" << endl;
            }
        }

        if (choice == '3') {

            if (language)
                cout << 
                        "1. Add Robot Welder\n" <<
                        "2. Output robot welders list\n" <<
                        "3. Welding detail\n" <<
                        "4. On robot\n" <<
                        "5. Del Robot Welder\n" << 
                        "0. Exit" << 
                endl;
            else 
                cout << 
                        "1. Agregar robot soldador\n" <<
                        "2. Salida de lista de soldadores robotizados\n" <<
                        "3. Detalle de soldadura\n" <<
                        "4. En robot\n" <<
                        "5. Del Robot Soldador\n" <<
                        "0. Salir" << 
                endl;
                    
            choice2 = getch();

            if (choice2 == '1') {
                    
                if (language)
                    cout << "NO \t Speed \t Time Welding \t Manipulator \t Radius" << endl;
                else 
                    cout << "NO \t Velocidad \t Tiempo Soldadura \t Manipulador \t Radio" << endl;
                
                do {
                    cin >> Speed >> TimeWelding >> Manipulator >> Radius;
                    if (Speed < 0 || 
                        TimeWelding < 0 || 
                        Manipulator < 0 || 
                        Radius < 0) {
                            language ? cout << "Enter normal data!" : cout << "Ingrese datos normales!";
                        }
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
                    cout << "Add minimum 1 welder robot" << endl;
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

    if (language)
        cout << "Goodbye!" << endl;
    else 
        cout << "Adios" << endl;


   
    i = 0;
    out.open(user_database_path_turners);
    if (out.is_open())
        for (Turner t : turners)
            out <<"\n" + to_string(++i) + " " + 
                        t.getFIO() + " " + 
                        to_string(t.getAge()) + " " + 
                        to_string(t.getStage()) + " " + 
                        to_string(t.getNumber());
        
    out.close();

    out.open(user_database_path_welders);
    if (out.is_open())
        for (Welder w : welders)
            out <<"\n" + to_string(++i) + " " + 
                        w.getFIO() + " " + 
                        to_string(w.getAge()) + " " + 
                        to_string(w.getStage()) + " " + 
                        to_string(w.getNumber()) + " " +
                        to_string(w.getExperience()) + " " +
                        to_string(w.getDepartament());
        
    out.close();

    return 0;
}
