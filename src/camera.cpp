#include "camera.h"

Camera::Camera(sf::RenderWindow *window) {
    
    this->view = sf::View(sf::FloatRect(0, 0, sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height));
    this->view.zoom(0.8);
    window->setView(view);
}

void Camera::MoveCamera(sf::RenderWindow *window, sf::Vector2f move) {
    this->view.move(move.x, move.y);
    window->setView(view);
}

void Camera::SetCenter(sf::RenderWindow *window, sf::Vector2f position) {
    
    this->view.setCenter(position.x, position.y);
    
    window->setView(view);
}

void Camera::Update(sf::RenderWindow *window, Map *map, sf::Vector2f position) {
    sf::Vector2f windowCenterStart = sf::Vector2f(window->getSize().x / 2, window->getSize().y / 2);
    sf::Vector2f windowCenterEnd = sf::Vector2f(map->width * map->tileWidth - windowCenterStart.x,
                                                map->height * map->tileHeight - windowCenterStart.y);

  // If map is smaller than window
    if(map->width * map->tileWidth < window->getSize().x
         && map->height * map->tileHeight < window->getSize().y) {
        this->SetCenter(window, sf::Vector2f(map->width * map->tileWidth / 2, map->height * map->tileHeight / 2));
    } else {
    // If Player is in the center (4)
       this->SetCenter(window, sf::Vector2f(position.x, position.y));
    }

    // If Player is in the edge (2,3)
    // Middle Top
    /*
    else if(position.x > windowCenterStart.x
    && position.x < windowCenterEnd.x
    && position.y < windowCenterStart.y) {

// If player is in the centre.
    if (position.x > windowCenterStart.x && position.y > windowCenterStart.y &&
        position.x < windowCenterEnd.x && position.y < windowCenterEnd.y) {
        this->SetCenter(window, sf::Vector2f(position.x, position.y));
    }
    else if (position.x > windowCenterStart.x && position.x < windowCenterEnd.x && position.y < windowCenterStart.y) {
        this->SetCenter(window, sf::Vector2f(position.x, windowCenterStart.y));
    }
    else if (position.x > windowCenterStart.x && position.x < windowCenterEnd.x && position.y > windowCenterEnd.y) {
        this->SetCenter(window, sf::Vector2f(position.x, windowCenterEnd.y));
    }
    else if (position.y > windowCenterStart.y && position.y < windowCenterEnd.y && position.x < windowCenterStart.x) {
        this->SetCenter(window, sf::Vector2f(windowCenterStart.x, position.y));
    }
    else if (position.y > windowCenterStart.y && position.y < windowCenterEnd.y && position.x > windowCenterEnd.x) {
        this->SetCenter(window, sf::Vector2f(windowCenterEnd.x, position.y));
    }
    else if (position.x < windowCenterStart.x && position.y < windowCenterStart.y) {
        this->SetCenter(window, sf::Vector2f(windowCenterStart.x, windowCenterStart.y));
    }
    else if (position.x > windowCenterEnd.x && position.y < windowCenterStart.y) {
        this->SetCenter(window, sf::Vector2f(windowCenterEnd.x, windowCenterStart.y));
    }
    else if (position.x < windowCenterStart.x && position.y > windowCenterEnd.y) {
        this->SetCenter(window, sf::Vector2f(windowCenterStart.x, windowCenterEnd.y));
    }
    else if (position.x > windowCenterEnd.x && position.y > windowCenterEnd.y) {
        this->SetCenter(window, sf::Vector2f(windowCenterEnd.x, windowCenterEnd.y));
    }
    */
    
}


bool Camera::IsOnScreen(sf::RenderWindow *window, Entity *entity) {
    if (entity->getPosition().x + entity->getGlobalBounds().width / 2 > this->view.getCenter().x - window->getSize().x / 2 &&
        entity->getPosition().x - entity->getGlobalBounds().width / 2 < this->view.getCenter().x + window->getSize().x / 2 &&
        entity->getPosition().y + entity->getGlobalBounds().height / 2 > this->view.getCenter().y - window->getSize().y / 2 &&
        entity->getPosition().y - entity->getGlobalBounds().height / 2 < this->view.getCenter().y + window->getSize().y / 2) {
        return true;
    }

    return false;
}

const sf::View& Camera::GetView() const {
    return this->view;
}

Camera::~Camera() {}