#ifndef OBJECTS_H
#define OBJECTS_H
#include<string>
#include<SFML/Graphics.hpp>
class Object
{
public:
    Object();
    ~Object();
    int GetPropertyInt(std::string name);
    float GetPropertyFloat(std::string name);
    std::string GetPropertyString(std::string name);

    std::string name;
    std::string type;
    sf::Rect<int> rect;
    std::map<std::string, std::string> properties;

    sf::Sprite *sprite;
};

#endif // OBJECTS_H
