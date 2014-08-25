#include "object.h"
#include<string>

#include<SFML/Graphics.hpp>

Object::Object(){
}

int Object::GetPropertyInt(std::string name){
    return atoi(properties[name].c_str());
}

float Object::GetPropertyFloat(std::string name){
    return strtod(properties[name].c_str(), NULL);
}

std::string Object::GetPropertyString(std::string name){
    return properties[name];
}

Object::~Object(){
    if(sprite!=nullptr)delete this->sprite;
}
