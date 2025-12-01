#ifndef WEAPON_H
#define WEAPON_H

#include <iostream>
#include <SFML/Graphics.hpp>

#include "camera.h"
#include "entitymanager.h"
#include "inputmanager.h"
#include "map.h"

class Weapon : public Entity
{
public:
    Weapon(Map* map, float x = 0, float y = 0);
    void Update(sf::RenderWindow *window, InputManager inputManager, int timeElapsed);
    float SetSpeed();
    int GetDamage();
    float GetSpeed();
    void Attack();
    ~Weapon();

private:
    Map* map;
    int damage;
    float speed;
    //float direction;
};

#endif // PLAYER_H
