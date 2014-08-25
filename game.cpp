#include "game.h"
#include <iomanip>
#include <sstream>
#define GAME_NAME "LostMiner"
#define GAME_VER "v0.01a"
#define LVLS_DIR "resources/levels/lvl"
Game::Game(){
    //считать конфиг-файл
    //применить парметры
    //получить значения текущего уровня
    current_lvl=0;
    CurrentLvl=new Level();
    ScreenSize=new sf::Vector2i(800, 600);
}
void Game::exec(){
    init();
    loop();
}

void Game::init(){
    CurrentLvl->LoadFromFile(get_src_lvl());
    world = new b2World(b2Vec2(0.0f, 1.0f));
    tileSize = CurrentLvl->GetTileSize();
    blocks= CurrentLvl->GetObjects("block");
    blocks_setup();
    player_setup();
    window_setup();
}

void Game::loop(){
    while(window.isOpen()){
        sf::Event evt;
        while(window.pollEvent(evt)){
            switch(evt.type){
            case sf::Event::Closed:
                window.close();
                return;
            }
        }
        Game::control();

        world->Step(1.0f / 15.0f, 10,10);

        b2Vec2 pos = playerBody->GetPosition();
        view.setCenter(pos.x + ScreenX/ 4, pos.y + ScreenY / 4);

        window.setView(view);

        player->sprite->setPosition(pos.x, pos.y);
        draw_all();
    }
}

void Game::control(){
    if(UP||DWN||LFT||RGHT){
        b2Vec2 vel = playerBody->GetLinearVelocity();
        if(UP && vel.y == 0){
               vel.y=-10;
        }
        if(DWN ){
           vel.y=10;
        }
        if(LFT ){
             vel.x=-5;
        }
        if(RGHT){
            vel.x=5;

        }
        std::cerr<<"\nvx: "<<vel.x<<" vy: "<<vel.y<<"\n";
        playerBody->SetLinearVelocity( vel );
    }
}

void Game::blocks_setup(){
    for(auto i : blocks){
        std::cerr<<i->name;
        b2BodyDef bodyDef;
        bodyDef.type = b2_staticBody;
        bodyDef.position.Set(i->rect.left + tileSize.x / 2 * (i->rect.width / tileSize.x - 1),
            i->rect.top + tileSize.y / 2 * (i->rect.height / tileSize.y - 1));
        b2Body* body = world->CreateBody(&bodyDef);
        b2PolygonShape shape;
        shape.SetAsBox(i->rect.width / 2, i->rect.height / 2);
        body->CreateFixture(&shape,1.0f);
    }
}

void Game::player_setup(){
    player = CurrentLvl->GetObject("player");
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(player->rect.left, player->rect.top);
    bodyDef.fixedRotation = true;
    playerBody = world->CreateBody(&bodyDef);
    b2PolygonShape shape;
    shape.SetAsBox(player->rect.width / 2, player->rect.height / 2);
    //b2CircleShape shape;
    //shape.m_radius=CurrentLvl->getTileHeight()/2;
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 1.0f; fixtureDef.friction = 1.3f;
    playerBody->CreateFixture(&fixtureDef);
}

void Game::window_setup(){
    window.create(sf::VideoMode(ScreenSize->x, ScreenSize->y), GAME_NAME);
    view.reset(sf::FloatRect(0.0f, 0.0f,  ScreenSize->x,  ScreenSize->y));
    view.setViewport(sf::FloatRect(0.0f, 0.0f, 2.0f,2.0f));
}

std::string Game::get_src_lvl(){
    return get_src_lvl(current_lvl);
}

std::string Game::get_src_lvl(unsigned custom_lvl){
    std::stringstream ss;
    ss << LVLS_DIR <<std::setfill('0') << std::setw(3) << custom_lvl<<".tmx";
    return ss.str();
}

void Game::draw_all(){
    window.clear();
    CurrentLvl->Draw(window);
    window.draw(*player->sprite);
    window.display();
}

Game::~Game(){
    delete CurrentLvl;
    delete world;
    delete ScreenSize;
}
