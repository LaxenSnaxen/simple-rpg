#ifndef ENTITYMANAGER
#define ENTITYMANAGER

#include <unordered_map>
#include <vector>

#include "camera.h"
#include "entity.h"

typedef void CollisionUpdateEvent(Entity* entityA, Entity* entityB);

class EntityManager
{
public:
    EntityManager();
    void SetCollisionMethod(CollisionUpdateEvent collisionsEvent);
    void AddEntity(std::string name, Entity *entity);
    Entity* Get(std::string name);
    void Update();
    void Render(sf::RenderWindow *window, Camera *camera);
    void SetMap(Map* map);
    ~EntityManager();
    void CaptureEntity(Entity &prisoner);

private:
    std::unordered_map<std::string, Entity*> entities;
    CollisionUpdateEvent* collisionsEvent;
    Map* map;
};

#endif // ENTITYMANAGER

