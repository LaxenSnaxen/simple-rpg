#include "weapon.h"

Weapon::Weapon(EntityManager* entityManager, Map *map, Camera *camera, float x, float y) {
    this->entityManager = entityManager;
    this->map = map;
    this->camera = camera;

    this->Load("data/gfx/OSTHYVEL.png");
    this->setPosition(x, y);
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
