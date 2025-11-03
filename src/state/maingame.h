#ifndef MAINGAME_H
#define MAINGAME_H

#include <iostream>

#include "camera.h"
#include "entitymanager.h"
#include "gamestate.h"
#include "inputmanager.h"
#include "mapload.h"
#include "player.h"

class MainGame : public GameState
{
public:
    void Initialize(sf::RenderWindow* window);
    void Update(sf::RenderWindow* window);
    void Render(sf::RenderWindow* window);
    void Destroy(sf::RenderWindow* window);

    void IncrementCoinCount();

private:
    sf::Clock clock;
    sf::Time time;

    EntityManager* entityManager;
    Map* map;
    Camera* camera;
    Player* player;

    sf::Clock clock;
    sf::Time time;
    EntityManager* entityManager;
    Map* map;
    Camera* camera;
    Player* player;

    int coinCount = 0;
};

#endif // MAINGAME_H
