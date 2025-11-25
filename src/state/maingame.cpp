#include "maingame.h"

void UpdateCollisions(Entity* entityA, Entity* entityB) {
    std::cout << "Collisions!" << entityA << std::endl;
}

void MainGame::Initialize(sf::RenderWindow* window) {
    this->entityManager = new EntityManager();
    this->entityManager->SetCollisionMethod(UpdateCollisions);

    // Add entities
    this->entityManager->AddEntity("test", new Entity("data/gfx/cheese.png"));
    this->entityManager->AddEntity("test0", new Entity("data/gfx/cheese.png"));
    this->entityManager->AddEntity("test1", new Entity("data/gfx/cheese.png"));
    this->entityManager->Get("test0")->velocity.x = 0.5;
    this->entityManager->Get("test")->setPosition(sf::Vector2f(50, 500));
    this->entityManager->Get("test0")->setPosition(sf::Vector2f(50, 300));
    this->entityManager->Get("test1")->velocity.x = 1.0f;
    this->entityManager->Get("test1")->setPosition(sf::Vector2f(50, 800));

    // Load Map
    this->map = new Map();
    MapLoad(this->map, "data/map/level1.json");

    // Load Camera
    this->camera = new Camera(window);


    // Load Player
    this->player = new Player(this->entityManager, this->map, this->camera, 100, 100);
    this->entityManager->AddEntity("Player", this->player);

    
    // Load Weapon
    this->weapon = new Weapon(this->map, 120, 90);
    this->entityManager->AddEntity("Weapon", this->weapon);
}

void MainGame::Update(sf::RenderWindow* window) {
    this->time = this->clock.getElapsedTime();
    int timeElapsed = this->time.asMicroseconds();
    this->clock.restart();

    this->player->Update(window, inputManager, timeElapsed);
    this->weapon->Update(window, inputManager, timeElapsed);
    this->entityManager->Update();
    this->map->CheckCollision(this->player);
    this->camera->Update(window, this->map, sf::Vector2f(this->player->getPosition().x, this->player->getPosition().y));

    this->weapon->setPosition(this->player->getPosition().x + 20, this->player->getPosition().y - 10);


    if(this->player->getPosition().x > 1510.0f) {
        std::cout << "You Win!" << std::endl;
        // next map code here
        MapLoad(this->map, "data/map/level2.json");
        this->player->setPosition(sf::Vector2f(100, 100));
        this->weapon->setPosition(sf::Vector2f(120, 90));
    }



    // Reloading of the map
    if(inputManager.IsPressed(InputManager::LoadMap)
    && inputManager.IsKeyBoardPressed(sf::Keyboard::LControl)) {
        std::cout << "Loading Map..." << std::endl;
        MapLoad(this->map, "data/map/level1.json", 0);
    }
    else if(inputManager.IsPressed(InputManager::LoadMap)) {
        std::cout << "Updating Map..." << std::endl;
        MapLoad(this->map, "data/map/level1.json", 1);
    }
}

void MainGame::Render(sf::RenderWindow* window) {
    this->map->RenderGround(window);
    this->entityManager->Render(window, this->camera);
    this->map->RenderAbove(window);
}

void MainGame::Destroy(sf::RenderWindow* window) {
    delete this->entityManager;
    delete this->map;
    delete this->camera;
}
