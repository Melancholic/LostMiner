#ifndef LEVELS_H
#define LEVELS_H
#include <string>
#include <vector>
#include <map>
#include <SFML/Graphics.hpp>
#include"object.h"
#include"layer.h"
#include"tileimg.h"
#include <tinyxml.h>
class Level{
public:
    Level();
    ~Level();
    bool LoadFromFile(std::string filename);
    Object *GetObject(std::string name);
    std::vector<Object *> GetObjects(std::string name);
    const std::vector<Object *> &GetObjects() const;
    std::vector<Layer> &GetLayers();
    void Draw(sf::RenderWindow &window);
    sf::Vector2i GetTileSize();
    TileImg* getTileIgFromGID(int);
    unsigned getTileWidth();
    unsigned getTileHeight();

private:
    int width, height, tileWidth, tileHeight;
    sf::Rect<float> drawingBounds;
    std::vector<Object *> objects;
    std::vector<Layer> layers;
    std::vector<TileImg*> tileImgArray;
    std::vector<sf::Rect<int> > subRects;
    bool loadTilesets(const TiXmlElement*);
    bool loadProps(const TiXmlElement*);
    bool loadLayers(const TiXmlElement*);
    bool loadObjects(const TiXmlElement*);
};
#endif // LEVELS_H

