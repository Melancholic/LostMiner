#include "layer.h"

Layer::Layer(){

}
int Layer::getOpacity(){
    return this->opacity;
}

void Layer::setOpacity(int op){
    opacity=op;
}

std::vector<sf::Sprite> &Layer::getTiles(){
    return tiles;
}

void Layer::setTiles( std::vector<sf::Sprite> &tls){
    tiles=tls;
}
