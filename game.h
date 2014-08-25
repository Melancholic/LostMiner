#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include "level.h"
#include<iostream>
#include <Box2D/Box2D.h>
#include <random>
#define ScreenX 800
#define ScreenY 600

#define UP sf::Keyboard::isKeyPressed(sf::Keyboard::W)
#define DWN sf::Keyboard::isKeyPressed(sf::Keyboard::S)
#define LFT sf::Keyboard::isKeyPressed(sf::Keyboard::A)
#define RGHT sf::Keyboard::isKeyPressed(sf::Keyboard::D)

class Game{
    unsigned current_lvl;
    Level *CurrentLvl;
    sf::Vector2i tileSize;
    b2World *world;
    sf::RenderWindow window;
    std::vector<Object*> blocks;
    Object* player;
    b2Body* playerBody;
    sf::Vector2i *ScreenSize;
    sf::View view;
    void init();
    void loop();
    void control();
    std::string get_src_lvl();
    std::string get_src_lvl(unsigned);
    void blocks_setup();
    void player_setup();
    void window_setup();
    void draw_all();
public:
    Game();
    void exec();
    ~Game();
};

#endif // GAME_H
