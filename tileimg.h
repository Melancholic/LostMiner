#ifndef TILEIMG_H
#define TILEIMG_H
#include"SFML/Graphics.hpp"

class TileImg{
    sf::Texture img;
    int minID;
    int maxID;
    int tileHeight;
    int tileWidth;

public:
    TileImg(std::string);
    TileImg();
    ~TileImg();
    int getMaxID();
    int getMinID();
    void setMaxID(int);
    void setMinID(int);
    void setImg(std::string);
    bool include(int gid);
    sf::Texture &getImg();
    int getTileWidth();
    int getTileHeight();
    void setTileHeight(int);
    void setTileWidth(int);

};

#endif // TILEIMG_H
