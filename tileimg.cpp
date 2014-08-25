#include "tileimg.h"
#include<climits>
#include<iostream>
TileImg::TileImg(){
    maxID=INT_MAX;
    minID=INT_MIN;
}

TileImg::TileImg(std::string){

}

int TileImg::getMaxID(){
    return maxID;
}

int TileImg::getMinID(){
    return minID;
}

void TileImg::setMaxID(int maxID){
    this->maxID=maxID;
}

void TileImg::setMinID(int minID){
    this->minID=minID;
}

bool TileImg::include(int gid){
    return (gid>=minID)&&(gid<=maxID);
}

sf::Texture &TileImg::getImg(){
    return img;
}

void TileImg::setImg(std::string src){
    sf::Image img_tmp;

    if(!img_tmp.loadFromFile("resources/images/"+src))
    {
      // std::cout << "Failed to load tile sheet." << std::endl;
        std::string error("Failed to load tile sheet.\n\tBecause:\"");
        error.append(src);
        error.append("\" not found!");
        throw error;
    }

    // Очищаем карту от света (109, 159, 185)
    img_tmp.createMaskFromColor(sf::Color(109, 159, 185));
    // Грузим текстуру из изображения
    img.loadFromImage(img_tmp);
    // Расплывчатость запрещена
    img.setSmooth(false);

}

int TileImg::getTileWidth(){
    return tileWidth;
}

int TileImg::getTileHeight(){
    return tileHeight;
}

void TileImg::setTileHeight(int val){
    tileHeight=val;
}

void TileImg::setTileWidth(int val){
    tileWidth=val;
}



TileImg::~TileImg(){

}
