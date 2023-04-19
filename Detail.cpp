#include "headers/Detail.h"

Detail::Detail() {};

Detail::Detail(int Size, string Name, string MetalType) {
    this->Size = Size;
    this->Name = Name;
    this->MetalType = MetalType;
};

void Detail::setSize(int Size) {this->Size = Size;}
int Detail::getSize() {return Size;}

void Detail::setName(string Name) {this->Name = Name;}
string Detail::getName() {return Name;}

void Detail::setMetalType(string MetalType) {this->MetalType = MetalType;}
string Detail::getMetalType() {return MetalType;}