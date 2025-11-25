#include "weapon.h"

Weapon::Weapon( Map *map, float x, float y) {
    this->map = map;
    this->Load("data/gfx/OSTHYVEL.png");
    this->setPosition(x, y);
    this->setScale(-2.5, 2.65);
    this->rotate(90);
    this->setOrigin(36, 5);
    this->speed = 0.00015f;
    this->damage = 10;
}

void Weapon::Update(sf::RenderWindow* window, InputManager inputManager, int timeElapsed) {
    float speed = this->speed * timeElapsed;
    // Update weapon velocity
    this->velocity.x = inputManager.IsPressed(InputManager::Right) * speed -
                       inputManager.IsPressed(InputManager::Left) * speed;
    this->velocity.y = inputManager.IsPressed(InputManager::Down) * speed -
                       inputManager.IsPressed(InputManager::Up) * speed;

    // Set correct speed on diagonal movement
    if((this->velocity.x == speed || this->velocity.x == -speed)
    && (this->velocity.y == speed || this->velocity.y == -speed)) {
        this->velocity.x *= .75;
        this->velocity.y *= .75;
    }

    if(this->velocity.x > 0) {
        this->setScale(-2.5, 2.65);
        this->setRotation(-270);
        this->setOrigin(36, 5);
    } else if(this->velocity.x < 0) {
        this->setScale(2.5, 2.65);
        this->setRotation(270);
        this->setOrigin(36, 57.7);
    };
}

int Weapon::GetDamage() {
    return this->damage;
}

void Weapon::Attack() {
    
}

float Weapon::GetSpeed() {
    return this->speed;
}

Weapon::~Weapon()
{

}
