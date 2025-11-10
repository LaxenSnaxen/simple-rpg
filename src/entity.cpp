#include "entity.h"
#include <iostream>

Entity::Entity() {
    this->active = 1;
    this->texture = new sf::Texture();
}

Entity::Entity(std::string fileName, int movementState) {
    this->active = 1;
    this->texture = new sf::Texture;
    this->Load(fileName);
    this->setOrigin((this->texture->getSize().x / 2), (this->texture->getSize().y / 2));
    this->movementState = movementState;
}

Entity::Entity(std::string fileName, sf::IntRect rect) {
    this->active = 1;
    this->texture = new sf::Texture();
    this->Load(fileName, rect);
    this->setOrigin((this->texture->getSize().x / 2), (this->texture->getSize().y / 2));
}

void Entity::Load(std::string fileName) {
    this->texture->loadFromFile(fileName, sf::IntRect());
    this->setTexture(*this->texture);
}

void Entity::Load(std::string fileName, sf::IntRect rect) {
    this->texture->loadFromFile(fileName, rect);
    this->setTexture(*this->texture);
}

bool Entity::Collision(Entity *entity) {
    if(entity != NULL) {
        return this->getGlobalBounds().intersects(entity->getGlobalBounds());
    }

    return false;
}

void Entity::SetActive(int active) {
    this->active = active;
}

int Entity::Active() {
    return this->active;
}

int Entity::Group() {
    return this->groupId;
}

void Entity::Update() {
    if (this->movementState == 1) {
        // Roaming beahviour, randomised movement.
        this->velocity.x += (rand() % 3 - 1) * 0.1;
        this->velocity.y += (rand() % 3 - 1) * 0.1;
        //std::cout << "Velocity: " << this->velocity.x << ", " << this->velocity.y << std::endl;
        this->move(this->velocity);
    }
    else{
        this->move(this->velocity);
    }
}

Entity::~Entity() {
    delete this->texture;
}
