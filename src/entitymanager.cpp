#include "entitymanager.h"
#include <vector>
#include "entity.h"
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Color.hpp>
#include "map.h"

EntityManager::EntityManager() {
}

void EntityManager::SetCollisionMethod(CollisionUpdateEvent collisionsEvent) {
    this->collisionsEvent = collisionsEvent;

}

void EntityManager::SetMap(Map* map) {
    this->map = map; // Set the Map instance
}

void EntityManager::AddEntity(std::string name, Entity* entity) {
    std::unordered_map<std::string, Entity*>::const_iterator found = this->entities.find(name);
    while(found != this->entities.end()) {
        name += "0";
        found = this->entities.find(name);
    }

    this->entities.insert(std::make_pair(name, entity));
}

Entity* EntityManager::Get(std::string name) {
    std::unordered_map<std::string, Entity*>::const_iterator found = this->entities.find(name);
    if(found != this->entities.end()) {
        return found->second;
    }

    return NULL;
}

void EntityManager::Update() {
    std::vector<std::string> toRemove;

    for (auto& iterator : this->entities) {
        this->map->CheckCollision(iterator.second);
        if (iterator.second != NULL) {
            if (this->collisionsEvent != NULL) {
                for (auto& iterator2 : this->entities) {
                    if (iterator != iterator2) {
                        if(iterator.second->Collision(iterator2.second)) {
                            this->collisionsEvent(iterator.second, iterator2.second);
                        }
                    }
                }
            }

            if (iterator.second->Active()) {
                iterator.second->Update();
            }
            else {
                toRemove.push_back(iterator.first);
            }
        }
    }

    while (toRemove.size() > 0) {
        this->entities.erase(toRemove[toRemove.size() - 1]);
        toRemove.pop_back();
    }

    toRemove.clear();
}


void EntityManager::Render(sf::RenderWindow* window, Camera *camera) {
    for(auto& iterator : this->entities) {
        if(iterator.second != NULL
        && iterator.second->Active()
        && camera->IsOnScreen(window, iterator.second)) {
            window->draw(*iterator.second);
        }
        // Check length to player
        if (iterator.second->calculateLength(Get("Player")) <= 100 && iterator.first != "Player") {
            // Will output a text bubble with the random dialogue option
            sf::Font font;
            if (!font.loadFromFile("data/ARIAL.TTF")) {
                exit(0);
            }
            sf::Text dialogue("", font, 20);
            dialogue.setFillColor(sf::Color::Black);
            sf::CircleShape shape(50.f);
            sf::Vector2f ShapePosition(iterator.second->getPosition().x, iterator.second->getPosition().y - 100);
            if (ShapePosition.x - 50 < 0 || ShapePosition.y - 50 < 0 || ShapePosition.x + 50 < -1280 || ShapePosition.y + 50 < -720) {
                continue;
            } else {
                dialogue.setString(iterator.second->Dialogue());
                // set the shape color to white
                shape.setFillColor(sf::Color(255, 255, 255));
                // Vet inte varför men helt plötsligt är nu stum fixa nästa gång
                shape.setPosition(ShapePosition);
                /*
                if (iterator.second->Dialogue() == L"Jag hörde att du fick en osthjul i \n huvudet under en klar natt. Är det därför \n du tror att månen är gjord av ost?") {
                    dialogue.setPosition(ShapePosition.x - 400, ShapePosition.y + 60);
                } else if (iterator.second->Dialogue() == L"Jag hörde att du inte tycker om färgen blå,\n är det på grund av blåmögelost?") {
                    dialogue.setPosition(ShapePosition.x - 200, ShapePosition.y + 60);
                } else if (iterator.second->Dialogue() == L"Om man tänker på det \n så har månen hål precis som ost" || iterator.second->Dialogue() == L"Om man tänker på det \nså är månen rund precis som ost" || iterator.second->Dialogue() == L"Om man tänker på det \nså är månen gul precis som ost") {
                    dialogue.setPosition(ShapePosition.x - 100, ShapePosition.y + 50);
                } else {
                    dialogue.setPosition(ShapePosition.x - 50, ShapePosition.y + 40);
                }
                */
                int numOfStringTerminator = 0;
                int characterSize = dialogue.getCharacterSize();
                std::string dialogueString = dialogue.getString();
                // comparison of integer expressions of different signedness: 'int' and 'std::__cxx11::basic_string<char>::size_type' {aka 'long long unsigned int'}
                // >:(
                for (long long unsigned int i = 0; i < dialogueString.length(); i++) {
                    if (dialogueString[i] == '\n') {
                        numOfStringTerminator += 5;
                    }
                }
                
                dialogue.setPosition(ShapePosition.x - (10 * (characterSize - (characterSize / 2) )), ShapePosition.y + numOfStringTerminator);

                window->draw(dialogue);
            }

        }
    }
}

EntityManager::~EntityManager() {
    for (auto& iterator : this->entities) {
        delete iterator.second;
    }

    this->entities.clear();
}
//callar på UpdateTexture och kollar för Collision och kollar om de är mögjligt 
void EntityManager::CaptureEntity(Entity &prisoner) {
    //call it when a collison happens between player and entity
    prisoner.UpdateTexture("data/gfx/test1.png");
}

