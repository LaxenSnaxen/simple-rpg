#include "map.h"

void TileSet::Clear() {
    while (this->tile.size() > 0) {
        delete this->tile[this->tile.size() - 1];
        this->tile.pop_back();
    }
}

TileSet::~TileSet() {
    this->Clear();
}

Map::Map() {
    this->ground1 = new Layer();
    this->ground2 = new Layer();
    this->ground3 = new Layer();
    this->above1 = new Layer();
    this->above2 = new Layer();
    this->above3 = new Layer();
    this->collision = new Layer();
    this->tileSet = new TileSet();
}

void Map::CheckCollision(Entity *entity) {
    // Get check section
    sf::Vector2f checkWidth = sf::Vector2f(
        (int)entity->getPosition().x / this->tileSet->tileWidth,
        (int)entity->getPosition().x / this->tileSet->tileWidth + 3
    );
    sf::Vector2f checkHeight = sf::Vector2f(
        (int)entity->getPosition().y / this->tileSet->tileWidth,
        (int)entity->getPosition().y / this->tileSet->tileWidth + 3
    );

    // Check collision
    int index;
    sf::Sprite tile;
    bool collided = false;
    sf::Vector2i collidedTile;
    for (int y = checkHeight.x; y < checkHeight.y; y++) {
        for (int x = checkWidth.x; x < checkWidth.y; x++) {
            index = this->collision->data[y][x];
            // If collision tile
            if(index != 0) {
                tile.setTexture(*this->tileSet->tile[index]);
                tile.setPosition(sf::Vector2f(x * this->tileSet->tileWidth, y * this->tileSet->tileHeight));
                // Rotate oblique collisions
//                if(i == 1) {
//                    switch(x) {
//                        case 3:
//                            break;

//                        case 4:
//                            break;

//                        case 5:
//                            break;
//                    }
//                }
                if (tile.getGlobalBounds().intersects(entity->getGlobalBounds())) {
                    collided = true;
                    collidedTile.x = x;
                    collidedTile.y = y;
                    break;
                }
            }
        }
    }

    // Move back if entity collided
    if(collided) {
        // Get Entities center x, y position;
        sf::Vector2i entityCenter = sf::Vector2i(
            (int)((entity->getPosition().x + entity->getGlobalBounds().width / 2) / this->tileSet->tileWidth),
            (int)((entity->getPosition().y + entity->getGlobalBounds().height / 2) / this->tileSet->tileHeight)
        );

        /*

        // DOWN_RIGHT
        if(collidedTile.x > entityCenter.x + 1
        && collidedTile.y > entityCenter.y + 1) {
            entity->velocity.x -= entity->velocity.x * 2;
            entity->velocity.y += entity->velocity.y * 2;
        }
        // UP_RIGHT
        else if(collidedTile.x > entityCenter.x + 1
        && collidedTile.y < entityCenter.y - 1) {
            entity->velocity.x -= entity->velocity.x * 2;
            entity->velocity.y -= entity->velocity.y * 2;
        }
        // UP_LEFT
        else if(collidedTile.x < entityCenter.x - 1
        && collidedTile.y < entityCenter.y - 1) {
            entity->velocity.x += entity->velocity.x * 2;
            entity->velocity.y -= entity->velocity.y * 2;
        }
        // DOWN_LEFT
        else if(collidedTile.x < entityCenter.x - 1
        && collidedTile.y > entityCenter.y + 1) {
            entity->velocity.x += entity->velocity.x * 2;
            entity->velocity.y += entity->velocity.y * 2;
        }

        // RIGHT
        if(collidedTile.x > entityCenter.x
        && collidedTile.y == entityCenter.y) {
            entity->velocity.x -= entity->velocity.x * 2;
        }
        // LEFT
        if(collidedTile.x < entityCenter.x
        && collidedTile.y == entityCenter.y) {
            entity->velocity.x += entity->velocity.x * 2;
        }
        // DOWN
        if(collidedTile.x == entityCenter.x
        && collidedTile.y > entityCenter.y) {
            entity->velocity.y += entity->velocity.y * 2;
        }
        // UP
        if(collidedTile.x == entityCenter.x
        && collidedTile.y < entityCenter.y) {
            entity->velocity.y -= entity->velocity.y * 2;
        }
        */

        // TODO: make sure collision really works, like print something when you collide
        // UP
        if (collidedTile.y + 1 == entityCenter.y) {
            entity->velocity.y -= entity->velocity.y * 2;
            std::cout << "UP!!" << std::endl;
        }
        
        if (collidedTile.y - 1 ==  entityCenter.y) {
            entity->velocity.y -= entity->velocity.y * 2;
            std::cout << "DOWN!!" << std::endl;
        }
        
        if (collidedTile.x + 1 == entityCenter.x) {
            entity->velocity.x -= entity->velocity.x * 2;
            std::cout << "RIGHT!!" << std::endl;
        }
        
        if (collidedTile.x - 1 == entityCenter.x) {
            entity->velocity.x -= entity->velocity.x * 2;
            std::cout << "LEFT!!" << std::endl;
        }

        std::cout << "Tile X: " << collidedTile.x << " : Player X: " << entityCenter.x << std::endl;
        std::cout << "Tile Y: " << collidedTile.y << " : Player Y: " << entityCenter.y << std::endl;
        std::cout << "----------------------------------" << std::endl;



        entity->move(entity->velocity.x, entity->velocity.y);
    }
}

void Map::RenderGround(sf::RenderWindow *window) {
    Layer* layer = this->ground1;
    this->Render(window, layer);

    layer = this->ground2;
    this->Render(window, layer);

    layer = this->ground3;
    this->Render(window, layer);
}

void Map::RenderAbove(sf::RenderWindow *window) {
    Layer* layer = this->above1;
    this->Render(window, layer);

    layer = this->above2;
    this->Render(window, layer);

    layer = this->above3;
    this->Render(window, layer);

//    layer = this->collision;
//    this->Render(window, layer);
}

void Map::Render(sf::RenderWindow *window, Layer *layer) {
    // Get render section
    sf::Vector2f renderWidth = sf::Vector2f(
        (window->getView().getCenter().x - window->getSize().x / 2) / this->tileWidth,
        (window->getView().getCenter().x + window->getSize().x / 2) / this->tileWidth
    );
    sf::Vector2f renderHeight = sf::Vector2f(
        (window->getView().getCenter().y - window->getSize().y / 2) / this->tileHeight,
        (window->getView().getCenter().y + window->getSize().y / 2) / this->tileHeight
    );

    // Render map
    int index;
    sf::Sprite tile;
    for (int y = renderHeight.x; y < renderHeight.y; y++) {
        for (int x = renderWidth.x; x < renderWidth.y; x++) {

            if(y > -1 &&  y < layer->data.size()) {
                if(x > -1 &&  x < layer->data.size()){
            index = layer->data[y][x];
            
            if(index != 0 && index <= this->tileSet->tile.size() ) {
                tile.setTexture(*this->tileSet->tile[index]);
                tile.setPosition(sf::Vector2f(x * this->tileSet->tileWidth, y * this->tileSet->tileHeight));
            
                    window->draw(tile);
                }
            }
            }
            
        }
    }
}

Map::~Map() {
    delete this->tileSet;
    delete this->ground1;
    delete this->ground2;
    delete this->ground3;
    delete this->above1;
    delete this->above2;
    delete this->above3;
    delete this->collision;
}
