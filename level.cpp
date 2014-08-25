#include "level.h"
#include<iostream>
#include<SFML/Graphics.hpp>
#include<map>
Level::Level(){
}
bool Level::loadProps(const TiXmlElement* map){
    width = atoi(map->Attribute("width"));
    height = atoi(map->Attribute("height"));
    tileWidth = atoi(map->Attribute("tilewidth"));
    tileHeight = atoi(map->Attribute("tileheight"));
    return true;
}

bool Level::LoadFromFile(std::string filename){
    TiXmlDocument levelFile(filename.c_str());
    if(!levelFile.LoadFile()){
        std::cerr << "Loading level \"" << filename << "\" failed:  "<< levelFile.ErrorDesc() << std::endl;
        return false;
    }
    TiXmlElement *map;
    map = levelFile.FirstChildElement("map");

    if(!loadProps(map)){
        return false;
    }
    if(!loadTilesets(map)){
        return false;
    }
    if(!loadLayers(map)){
        return false;
    }
    if(!loadObjects(map)){
        return false;
    }

    return true;
}

bool Level::loadTilesets(const TiXmlElement* map){
    const TiXmlElement *tsElem;
    tsElem = map->FirstChildElement("tileset");
    //for( tsElem = map->FirstChildElement("tileset"); tsElem->Attribute("firstgid"); tsElem = tsElem->NextSiblingElement() ){
    while( tsElem->Attribute("firstgid")){
    TileImg* tile=new TileImg();
        tile->setMinID(atoi(tsElem->Attribute("firstgid")));
        tile->setTileWidth(tileWidth);
        tile->setTileHeight(tileHeight);
        if(this->tileImgArray.size()!=0){
            tileImgArray.at(tileImgArray.size()-1)->setMaxID(tile->getMinID()-1);
        }
    const TiXmlElement *image = tsElem->FirstChildElement("image");
    try{
        tile->setImg(image->Attribute("source"));
    }catch(std::string e){
        std::cerr<<e;
        return false;
    }
    tileImgArray.push_back(tile);
    int columns = tile->getImg().getSize().x / tileWidth;
    int rows =  tile->getImg().getSize().y / tileHeight;
    for(int y = 0; y < rows; y++)
    for(int x = 0; x < columns; x++)    {
        sf::Rect<int> rect;
        rect.top = y * tileHeight;
        rect.height = tileHeight;
        rect.left = x * tileWidth;
        rect.width = tileWidth;
        subRects.push_back(rect);
    }
         tsElem = tsElem->NextSiblingElement();
    }
    return true;
}
bool Level::loadLayers(const TiXmlElement* map){
    const TiXmlElement *layerElement = map->FirstChildElement("layer");
    while(layerElement){
        Layer layer;
        if (layerElement->Attribute("opacity") != NULL){
            float opacity = strtod(layerElement->Attribute("opacity"), NULL);
            layer.setOpacity(255 * opacity);
        }
        else{
            layer.setOpacity(255);
        }
        const TiXmlElement *layerDataElement = layerElement->FirstChildElement("data");
        if(layerDataElement == NULL){
            std::cout << "Bad map. No layer information found." << std::endl;
        }

        const TiXmlElement *tileElement;
        tileElement = layerDataElement->FirstChildElement("tile");

        if(tileElement == NULL){
            std::cout << "Bad map. No tile information found." << std::endl;
            return false;
        }
        int x = 0;
        int y = 0;
        while(tileElement){
            int tileGID = atoi(tileElement->Attribute("gid"));
            for(auto i:tileImgArray){
                if (i->include(tileGID)){
                    sf::Sprite sprite;
                    sprite.setTexture(i->getImg());
                    sprite.setTextureRect(subRects[tileGID-1/*-i->getMinID()*/]);
                    sprite.setPosition(x * i->getTileWidth(), y * i->getTileHeight());
                    sprite.setColor(sf::Color(255, 255, 255, layer.getOpacity()));
                    layer.getTiles().push_back(sprite);
                }
            }
            tileElement = tileElement->NextSiblingElement("tile");
            x++;
            if (x >= width){
                x = 0;
                y++;
                if(y >= height){
                    y = 0;
                }
            }
        }

        layers.push_back(layer);
        layerElement = layerElement->NextSiblingElement("layer");
    }
    return true;
}

bool Level::loadObjects(const TiXmlElement* map){
    const TiXmlElement *objectGroupElement;
    if (map->FirstChildElement("objectgroup") != NULL){
        objectGroupElement = map->FirstChildElement("objectgroup");
        while (objectGroupElement){
            const TiXmlElement *objectElement;
            objectElement = objectGroupElement->FirstChildElement("object");
            while(objectElement){
                std::string objectType;
                if (objectElement->Attribute("type") != NULL){
                    objectType = objectElement->Attribute("type");
                }
                std::string objectName;
                if (objectElement->Attribute("name") != NULL){
                    objectName = objectElement->Attribute("name");
                }
                int x = atoi(objectElement->Attribute("x"));
                int y = atoi(objectElement->Attribute("y"));
                int width, height;
                Object *object=new Object();
                if (objectElement->Attribute("width") != NULL){
                    width = atoi(objectElement->Attribute("width"));
                    height = atoi(objectElement->Attribute("height"));
                    object->sprite = nullptr;
                }else{
                    int obj_id= atoi(objectElement->Attribute("gid"));
                    TileImg *obj_tileImg;
                    if(!(obj_tileImg=getTileIgFromGID(obj_id))){
                        std::cerr<<"\nERROR: Not founded tile with gid="<<obj_id<<std::endl;
                        return false;
                    }
                    sf::Sprite *sprite=new sf::Sprite();
                    sprite->setTexture(obj_tileImg->getImg());
                    sprite->setTextureRect(sf::Rect<int>(0,0,0,0));
                     // sprite->setTextureRect(subRects[obj_id-obj_tileImg->getMinID()]);
                    sprite->setPosition(x, y);
                    std::cerr<<"x: "<<x<<"y: "<<y;
                    width = subRects[atoi(objectElement->Attribute("gid")) - obj_tileImg->getMinID()].width;
                    height = subRects[atoi(objectElement->Attribute("gid")) - obj_tileImg->getMinID()].height;
                    sprite->setTextureRect(subRects[atoi(objectElement->Attribute("gid"))-1 /*- obj_tileImg->getMinID()*/]);
                    object->sprite = sprite;
                }
                object->name = objectName;
                object->type = objectType;
                sf::Rect <int> objectRect;
                objectRect.top = y;
                objectRect.left = x;
                objectRect.height = height;
                objectRect.width = width;
                object->rect = objectRect;


                const TiXmlElement *properties;
                properties = objectElement->FirstChildElement("properties");
                if (properties != NULL){
                    const TiXmlElement *prop;
                    prop = properties->FirstChildElement("property");
                    if (prop != NULL){
                        while(prop){
                            std::string propertyName = prop->Attribute("name");
                            std::string propertyValue = prop->Attribute("value");
                            object->properties[propertyName] = propertyValue;
                            prop = prop->NextSiblingElement("property");
                        }
                    }
                }
                objects.push_back(object);
                objectElement = objectElement->NextSiblingElement("object");
            }
            objectGroupElement = objectGroupElement->NextSiblingElement("objectgroup");
        }
    }else{
        std::cout << "No object layers found..." << std::endl;
    }
    return true;
}


Object *Level::GetObject(std::string name){
    // First finded object with name
    for (auto i : objects){
        if (i->name == name){
            return i;
        }
    }
    return nullptr;
}

std::vector<Layer> &Level::GetLayers(){
    return this->layers;
}

std::vector<Object *> Level::GetObjects(std::string name){
    // All finded object with name
    std::vector<Object*> res;
    for(auto i :objects)
        if(i->name == name)
            res.push_back(i);
    return res;
}

const std::vector<Object *> &Level::GetObjects() const{
   return objects;
}

sf::Vector2i Level::GetTileSize(){
    return sf::Vector2i(tileWidth, tileHeight);
}

unsigned Level::getTileWidth(){
    return tileWidth;
}

unsigned Level::getTileHeight(){
    return tileHeight;
}

void Level::Draw(sf::RenderWindow &window){
    //Draw Tiled
    //Objects draw in Game
    for(unsigned layer = 0; layer < layers.size(); layer++)
        for(unsigned tile = 0; tile < layers[layer].getTiles().size(); tile++)
            window.draw(layers[layer].getTiles()[tile]);
}
TileImg* Level::getTileIgFromGID(int gid){
    for(auto i: this->tileImgArray){
        if(i->include(gid)){
            return i;
        }
    }
    return 0;
}

Level::~Level(){
    for(auto i: this->tileImgArray){
        delete i;
    }
    for(auto i: objects){
        delete i;
    }

}

