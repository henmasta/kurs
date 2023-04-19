#include "headers/Employee.h"

void Employee::setFIO(string FIO) { 
    FIO = this->FIO; 
}

string Employee::getFIO() { 
    return FIO;   
}
        
void Employee::setNumber(int Number) { 
    this->Number = Number; 
}

int Employee::getNumber() { 
    return Number; 
}

void Employee::setAge(int Age) { 
    this->Age = Age; 
}

int Employee::getAge() { 
    return Age;    
}

void Employee::setStage(int Stage)  { 
    this->Stage = Stage;  
}

int Employee::getStage()  { 
    return Stage;  
}        
