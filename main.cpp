#include <map>
#include <dir.h>
#include <regex>
#include <vector>
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
        robot_welder_file >> Speed;
        robot_welder_file >> TimeWelding;
        robot_welder_file >> Manipulator;
        robot_welder_file >> Radius;
        

        RobotWelder robot_welder(Speed, TimeWelding, Manipulator, Radius);
        rbt.push_back(robot_welder);
    }

    return rbt;

}


vector<Detail> push_from_file_detail(vector<Detail> det, string file) {
    
    int NO;
    int Size;
    string Name;
    string MetalType;    


    if (last_line(file) <= 1) return det;
    
    ifstream detail_file(file);

    if(!detail_file && !exists(file)) {
        cout << "error open file " << file << endl;
        ofstream (file);
        return det;
    }
    
    while (!detail_file.eof()){
        detail_file >> NO;
        detail_file >> Size;
        detail_file >> Name;
        detail_file >> MetalType;

        Detail detail(Size, Name, MetalType);
        det.push_back(detail);
    }

    return det;

}



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
                
                if (regex_match(path_folders, regex("[A-Za-z0-9]")))
                    throw "not created";

                mkdir(path_folders_to_char);
                if (!exists(path_folders)) 
                    throw "not created";
            } catch (...){
                cerr << "path not created \nuncorrected name" << endl;
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

                

                out.open(user_database_path);
                out.close();
            }
        }
        path_folders = "";
        file_path_name = "";      
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
    
    
    int ch, choice, choice2, choice3;
    
    //Turner turner("pety", 22, 2, 153);
    //Detail dett(20, "detail1", "fe");
    //turners.push_back(turner);
    //details.push_back(dett);

    string  user_database_path_turners,
            user_database_path_welders,
            user_database_path_robot_welders,
            user_database_path_detail;

    string first_turner, first_welder, first_robot_welder, first_detail;
    

    system("cls");

    cout << "Enter path for turners to database(for standart path \"database/turners.txt\" type 0): ";
    cin >> user_database_path_turners;
    first_turner = user_database_path_turners[0]; 

    set_path_to_database(user_database_path_turners, first_turner, "database/turners.txt", out); 

    cout << "Enter path for welders to database(for standart path \"database/welders.txt\" type 0): ";
    cin >> user_database_path_welders;
    first_welder = user_database_path_welders[0];

    set_path_to_database(user_database_path_welders, first_welder, "database/welders.txt", out);  

    cout << "Enter path for robot welders to database(for standart path \"database/robot_welders.txt\" type 0): ";
    cin >> user_database_path_robot_welders;
    first_robot_welder = user_database_path_robot_welders[0];

    set_path_to_database(user_database_path_robot_welders, first_robot_welder, "database/robot_welders.txt", out);

    cout << "Enter path for robot welders to database(for standart path \"database/details.txt\" type 0): ";
    cin >> user_database_path_detail;
    first_detail = user_database_path_detail[0];
    
    set_path_to_database(user_database_path_detail, first_detail, "database/detail.txt", out);    

    if(!first_turner.compare("0"))
        user_database_path_turners = "database/turners.txt";
    
    if(!first_welder.compare("0"))
        user_database_path_welders = "database/welders.txt";

    if(!first_robot_welder.compare("0"))
        user_database_path_robot_welders = "database/robot_welders.txt";

    if(!first_detail.compare("0"))
        user_database_path_detail = "database/detail.txt";



    if (exists(user_database_path_turners)) {
        turners = push_from_file_turner(turners, user_database_path_turners);
    }

    if (exists(user_database_path_welders)) {
        welders = push_from_file_welder(welders, user_database_path_welders);
    }

    if (exists(user_database_path_robot_welders)) {
        robot_welders = push_from_file_robot_welder(robot_welders, user_database_path_robot_welders);
    }

    if (exists(user_database_path_detail)) {
        details = push_from_file_detail(details, user_database_path_detail);
    }

    do {

        system("cls");
        if(language)
            path_to_lang = "interface/eng/";
        else 
            path_to_lang = "interface/isp/";

        
        read_from_file(path_to_lang + "logo.txt");

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

            if (choice2 == 9)  {
                if (language)
                    cout << "Language replaced" << endl;
                else 
                    cout << "Idioma reemplazado" << endl;
                language = !language;
                
            }

            if (choice2 == '0') {
                break;
            }

            if (choice2 == '1') {

                if (language)
                    cout << "FIO \t Age \t Stage \t Number" << endl;
                else
                    cout << "FIO \t Edad \t Etapa \t Numero" << endl;
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
                            if (n < 0 || n > i) cout << "Enter correctly number" << endl;
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
                cout << "Up stage for: " << endl;

                if (language)
                    cout << "FIO \t Age \t Stage \t Number" << endl;
                else
                    cout << "FIO \t Edad \t Etapa \t Numero" << endl;

                for(Turner t : turners) 
                    cout << to_string(++i) + ". " + t.getFIO() << " \t " << 
                                                    t.getAge() << " \t " << 
                                                    t.getStage() << " \t " << 
                                                    t.getNumber() << endl;

                do {
                    cin >> n;
                    fflush(stdin);
                } while (n < 0 || n > i);

                ++turners.at(n-1);
            }


            if (choice2 == '6') {

                i = 0;

                if (language)
                    cout << "FIO \t Age \t Stage \t Number" << endl;
                else
                    cout << "FIO \t Edad \t Etapa \t Numero" << endl;

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
                    language ? cout << "Not exists!" << endl : cout << "No existe!" << endl;
            }

            

        }

        if (choice == '2') {
            read_from_file(path_to_lang + "welder_main_menu.txt");
            
            choice2 = getch();

            if (choice2 == 9)  {
                if (language)
                    cout << "Language replaced" << endl;
                else 
                    cout << "Idioma reemplazado" << endl;
                language = !language;
                
            }

            if (choice2 == '0') {
                break;
            }

            if (choice2 == '1') {

                if (language)
                    cout << "FIO \t Age \t Stage \t Number \t Experience \t Departament" << endl;
                else
                    cout << "FIO \t Edad \t Etapa \t Número \t Experiencia \t Departamento" << endl;
                cin >> FIO >> Age >> Stage >> Number >> Experience >> Departament;

                Welder welder(FIO, Age, Stage, Number, Experience, Departament);            
            
                welders.push_back(welder);
                cout << "OK" << endl;

            }

            if (choice2 == '2') {
                i = 0;
                cout << "Welders: " << endl;
                if (language)
                    cout << "FIO \t Age \t Stage \t Number \t Experience \t Departament" << endl;
                else
                    cout << "FIO \t Edad \t Etapa \t Número \t Experiencia \t Departamento" << endl;

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

                    if (language)
                        cout << "FIO \t Age \t Stage \t Number \t Experience \t Departament" << endl;
                    else
                        cout << "FIO \t Edad \t Etapa \t Número \t Experiencia \t Departamento" << endl;
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
                        if (n < 0 || n > i) cout << "Enter correctly number" << endl;
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

                if (language)
                    cout << "FIO \t Age \t Stage \t Number" << endl;
                else
                    cout << "FIO \t Edad \t Etapa \t Numero" << endl;

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

            read_from_file(path_to_lang + "robot_welder_main_menu.txt");
                    
            choice2 = getch();


            if (choice2 == 9)  {
                if (language)
                    cout << "Language replaced" << endl;
                else 
                    cout << "Idioma reemplazado" << endl;
                language = !language;
                
            }
            if (choice2 == '0') {
                break;
            }

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
                if (language)
                    cout << "NO \t Speed \t Time Welding \t Manipulator \t Radius" << endl;
                else 
                    cout << "NO \t Velocidad \t Tiempo Soldadura \t Manipulador \t Radio" << endl;

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

                    if (language)
                        cout << "NO \t Speed \t Time Welding \t Manipulator \t Radius" << endl;
                    else 
                        cout << "NO \t Velocidad \t Tiempo Soldadura \t Manipulador \t Radio" << endl;

                    for(RobotWelder r : robot_welders) 
                        cout << to_string(++i) + ". " + to_string(r.getSpeed()) << "\t"
                            << r.getTimeWelding() << "\t"
                            << r.getManipulator() << "\t"
                            << r.getRadius()
                        << endl;
                    
                    do {
                        language ? cout << "Enter robot welder number: " : cout << "Introduzca el numero de robot soldador: ";
                        cin >> n;
                        if (n < 0 || n > i) cout << "Enter correctly number" << endl;
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
                i = 0;
                cout << "Number robot for on/off: " << endl;
                for(RobotWelder r : robot_welders) 
                        cout << to_string(++i) + ". " + to_string(r.getSpeed()) << "\t"
                            << r.getTimeWelding() << "\t"
                            << r.getManipulator() << "\t"
                            << r.getRadius()
                        << endl;
                do {
                    cin >> n;
                    if (n < 0 || n > i) cout << "Enter correctly number" << endl;
                } while(n < 0 || n > i);
                robot_welders.at(n-1).Power();
            }


            if (choice2 == '5') {

                i = 0;

                if (!robot_welders.empty()) {

                    cout << "Enter number robot for rotation: " << endl;

                    for (RobotWelder r : robot_welders)
                        cout << to_string(++i) + " " + 
                                to_string(r.getSpeed()) + " " +
                                to_string(r.getTimeWelding()) + " " +
                                to_string(r.getManipulator()) + " " +
                                to_string(r.getRadius()) 
                        << endl;

                    do {
                        cin >> n;
                        if (n < 0 || n > i) cout << "Enter correctly number" << endl;
                        fflush(stdin);
                    } while(n < 0 || n > i);

                    float Move_num;
                    cout << "Enter how far to turn: ";
                    cin >> Move_num;

                    robot_welders.at(n-1).Move(Move_num);
                } else {
                    cout << "Add minimum 1 robot welder" << endl;
                }
            }

            if (choice2 == '6') {
                i = 0;

                if (!robot_welders.empty()) {
                    
                    language ? cout << "Robots welders: " << endl : cout << "Robots soldadores: " << endl;
                    
                    for (RobotWelder r : robot_welders)
                        cout << to_string(++i) + " " + 
                                to_string(r.getSpeed()) + " " +
                                to_string(r.getTimeWelding()) + " " +
                                to_string(r.getManipulator()) + " " +
                                to_string(r.getRadius()) 
                        << endl;
                    do {
                        cout << "Number robot welder for delete: ";
                        cin >> n;
                        if (n < 0 || n > i) cout << "Enter correctly number" << endl;
                    } while(n < 0 || n > i);
                    cout << "Robot welder with name " << robot_welders.at(n-1).getName() << " delete" << endl;

                    robot_welders.erase(robot_welders.begin() + n-1);
                } else {
                    cout << "Add minimum 1 detail" << endl;
                }   
            }


        }

        if (choice == '4') {

            read_from_file(path_to_lang + "detail_main_menu.txt");

            choice2 = getch();

            if (choice2 == 9)  {
                if (language)
                    cout << "Language replaced" << endl;
                else 
                    cout << "Idioma reemplazado" << endl;
                language = !language;
                
            }

            if (choice2 == '0') {
                break;
            }

            if (choice2 == '1') {

                if (language)
                    cout << "  Size \t Name \t Metal Type" << endl;
                else
                    cout << "  Tamano \t Nombre \t Tipo de metal" << endl;

                cin >> Size >> Name >> MetalType;

                Detail detail(Size, Name, MetalType);

                int m = 0;

                for (Detail d : details)
                    if (detail == d) {
                        m++;
                    }
                if (m > 0) {
                    cout << "Create a part with a different name!" << endl;
                }

                if (m == 0){
                    details.push_back(detail);
                    cout << "OK" << endl;
                }
                
                
            }


            if (choice2 == '2') {
                
                i = 0;

                if (language)
                    cout << "  Size \t Name \t Metal Type" << endl;
                else
                    cout << "  Tamano \t Nombre \t Tipo de metal" << endl;

                if (!details.empty()) {
                    for(Detail d : details) 
                        cout << to_string(++i) + ". " + to_string(d.getSize()) << " \t " << 
                                                                d.getName() << " \t " << 
                                                                d.getMetalType() << endl; 
                } else {
                    if(language)
                        cout << "Add minimum 1 detail" << endl;
                    else 
                        cout << "Agregar minimo 1 detalle" << endl;
                }   
            }

            if (choice2 == '3') {
                
                i = 0;

                if (!details.empty()) {
                    
                    language ? cout << "Details: " << endl : cout << "Detalle: " << endl;
                    
                    for(Detail d : details) 
                        cout << to_string(++i) + ". " + to_string(d.getSize()) << " \t " << 
                                                                d.getName() << " \t " << 
                                                                d.getMetalType() << endl; 
                    do {
                        cout << "Number detail for delete: ";
                        cin >> n;
                        if (n < 0 || n > i) cout << "Enter correctly number" << endl;
                    } while(n < 0 || n > i);
                    cout << "Detail with name " << details.at(n-1).getName() << " delete" << endl;

                    details.erase(details.begin() + n-1);
                } else {
                    cout << "Add minimum 1 detail" << endl;
                }   
            }
        }

        if (choice == '5') {
            cout << "Total objects: " +  to_string(turners.size() + mach.size() + details.size() + welders.size() + robot_welders.size()) << endl;

            cout << "Total turners: " + to_string(turners.size()) << endl;
            cout << "Total Turner Machine turners: " + to_string(mach.size()) << endl;
            cout << "Total Details turners: " + to_string(details.size()) << endl;
            cout << "Total Welders turners: " + to_string(welders.size()) << endl;
            cout << "Total Robot Welders: " + to_string(robot_welders.size()) << endl;
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

    i = 0;
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

    i = 0;
    out.open(user_database_path_robot_welders);
    if (out.is_open())
        for (RobotWelder r : robot_welders)
            out <<"\n" + to_string(++i) + " " + 
                        to_string(r.getSpeed()) + " " +
                        to_string(r.getTimeWelding()) + " " +
                        to_string(r.getManipulator()) + " " +
                        to_string(r.getRadius());
        
    out.close();

    i = 0;
    out.open(user_database_path_detail);
    if (out.is_open())
        for (Detail d : details)
            out <<"\n" + to_string(++i) + " " + 
                        to_string(d.getSize()) + " " +
                        d.getName() + " " +
                        d.getMetalType();
        
    out.close();

    system("pause");
    return 0;
}
