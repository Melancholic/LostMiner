#ifndef LAYERS_H
#define LAYERS_H
#include"vector"
#include"SFML/Graphics.hpp"

class Layer{
    int opacity;
    std::vector<sf::Sprite> tiles;
public:
    Layer();
    int getOpacity();
    void setOpacity(int);
    std::vector<sf::Sprite>& getTiles();
    void setTiles(std::vector<sf::Sprite>&);
};

#endif // LAYERS_H
