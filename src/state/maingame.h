#ifndef MAINGAME_H
#define MAINGAME_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include "camera.h"
#include "entitymanager.h"
#include "gamestate.h"
#include "inputmanager.h"
#include "mapload.h"
#include "player.h"

class MainGame : public GameState
{
public:
    void Initialize(sf::RenderWindow* window) override;
    void Update(sf::RenderWindow* window) override;
    void Render(sf::RenderWindow* window) override;
    void Destroy(sf::RenderWindow* window) override;

    void IncrementCoinCount();

private:
    sf::Clock clock;
    sf::Time time;

    EntityManager* entityManager;
    Map* map;
    Camera* camera;
    Player* player;

    sf::Font font;
    int coinCount = 0;
};

#endif // MAINGAME_H