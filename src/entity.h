#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <SFML/Graphics.hpp>
#include <vector>

class Entity : public sf::Sprite
{
public:
    Entity();
    Entity(std::string fileName);
    Entity(std::string fileName, sf::IntRect rect);
    void Load(std::string fileName);
    void Load(std::string fileName, sf::IntRect rect);
    bool Collision(Entity *entity);
    void SetActive(int active);
    std::wstring Dialogue();
    void setDialogue(std::vector<std::wstring> dialogue_options);
    int Active();
    int Group();
    virtual void Update();
    ~Entity();

    sf::Vector2f velocity;
    bool hasSpoken = false;
    std::wstring dialogue_option;

protected:
    int active, groupId;

private:
    sf::Texture* texture;
    std::vector<std::wstring> dialogue_options;
};

#endif // ENTITY_H
