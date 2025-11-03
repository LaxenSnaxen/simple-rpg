#include "maingame.h"
#include "coin.h"

void UpdateCollisions(Entity* entityA, Entity* entityB) {
    Player* player = dynamic_cast<Player*>(entityA);
    Coin* coin = dynamic_cast<Coin*>(entityB);

    if (!player) {
        player = dynamic_cast<Player*>(entityB);
        coin = dynamic_cast<Coin*>(entityA);
    }

    if (player && coin && coin->Active()) {
        std::cout << "Player picked up a coin!" << std::endl;
        coin->SetActive(0);

        // Increment global counter
        MainGame* mainGame = dynamic_cast<MainGame*>(gameState.state);
        if (mainGame) {
            mainGame->IncrementCoinCount();
        }
    }
}

void MainGame::Initialize(sf::RenderWindow* window) {
    this->entityManager = new EntityManager();
    this->entityManager->SetCollisionMethod(UpdateCollisions);

    // Add entities
    this->entityManager->AddEntity("test", new Entity("data/gfx/test.png", 0));
    this->entityManager->AddEntity("test", new Entity("data/gfx/test.png", 1));
    this->entityManager->Get("test")->velocity.x = 0.5;
    //this->entityManager->Get("test0")->velocity.x = 0.5;
    this->entityManager->Get("test")->setPosition(sf::Vector2f(50, 50));
    this->entityManager->Get("test0")->setPosition(sf::Vector2f(50, 300));

    // Load Map
    this->map = new Map();
    MapLoad(this->map, "data/map/level1.json");

    // Load Camera
    this->camera = new Camera(window);

    // Load Player
    this->player = new Player(this->entityManager, this->map, this->camera, 100, 100);
    this->entityManager->AddEntity("Player", this->player);

    // Load Coins
    this->entityManager->AddEntity("Coin", new Coin(140, 100));
    this->entityManager->AddEntity("Coin", new Coin(200, 150));
    this->entityManager->AddEntity("Coin", new Coin(300, 200));
    this->entityManager->AddEntity("Coin", new Coin(450, 250));
    this->entityManager->AddEntity("Coin", new Coin(600, 300));
}

void MainGame::Update(sf::RenderWindow* window) {
    this->time = this->clock.getElapsedTime();
    int timeElapsed = this->time.asMicroseconds();
    this->clock.restart();

    this->player->Update(window, inputManager, timeElapsed);
    this->entityManager->Update();
    this->map->CheckCollision(this->player);
    this->camera->Update(window, this->map, sf::Vector2f(this->player->getPosition().x, this->player->getPosition().y));

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

void MainGame::IncrementCoinCount() {
    coinCount++;
    std::cout << "Coins collected: " << coinCount << std::endl;
}