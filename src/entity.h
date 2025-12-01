#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <SFML/Graphics.hpp>
#include <vector>

class Entity : public sf::Sprite
{
public:
    Entity();
    Entity(std::string fileName, int movementState = 0);
    Entity(std::string fileName, sf::IntRect rect);
    void Load(std::string fileName);
    bool Collision(Entity *entity);
    void SetActive(int active);
    std::wstring Dialogue();
    void setDialogue(std::vector<std::wstring> dialogue_options);
    float calculateLength(Entity* entity);
    int Active();
    int Group();
    virtual void Update();
    void UpdateTexture(std::string filePath);
    ~Entity();
    
    sf::Vector2f velocity;
    bool hasSpoken = false;
    std::wstring dialogue_option;

    bool status;
    bool isPlayer;
protected:
    int active, groupId, movementState;

private:
    sf::Texture* texture;
    std::vector<std::wstring> dialogue_options;
};

#endif // ENTITY_H
