#include "maingame.h"
#include "entity.h"

#include <SFML/Graphics.hpp>

void UpdateCollisions(Entity* entityA, Entity* entityB) {
    std::cout << "Collisions!" << std::endl;
    if(inputManager.IsKeyBoardPressed(sf::Keyboard::C)) {
        if(entityB->isPlayer != true ) {
            entityB->velocity.x = 0;
            entityB->status= true;
            entityB->UpdateTexture("data/gfx/test1.png");            
        }else if(entityA->isPlayer != true) {
            entityA->velocity.x = 0;
            entityA->status= true;
            entityA->UpdateTexture("data/gfx/test1.png");
        }
    }
  
    Player* player = dynamic_cast<Player*>(entityA);
    Coin* coin = dynamic_cast<Coin*>(entityB);

    if (!player) {
        player = dynamic_cast<Player*>(entityB);
        coin = dynamic_cast<Coin*>(entityA);
    }

    if (player && coin && coin->Active()) {
        std::cout << "Player picked up a coin!" << std::endl;
        coin->SetActive(0);

        MainGame* mainGame = dynamic_cast<MainGame*>(gameState.GetState());
        if (mainGame) {
            mainGame->IncrementCoinCount();
        }
    }
}

void MainGame::Initialize(sf::RenderWindow* window) {
    this->entityManager = new EntityManager();
    this->entityManager->SetCollisionMethod(UpdateCollisions);

    std::vector<std::wstring> dialogue_options = 
    {L"Så det är du som är Johan Ostman", 
        L"Jag hörde att du fick ett \nosthjul i huvudet under en klar natt.\n Är det därför du tror att månen är gjord av ost?", 
        L"Om man tänker på det \n så har månen hål precis som ost", 
        L"Om man tänker på det \nså är månen rund precis som ost", 
        L"Om man tänker på det \nså är månen gul precis som ost", 
        L"Jag hörde att du inte tycker om färgen blå, \när det på grund av blåmögelost?"};
    
    // Add NPCs
    Entity *ptr0 = new Entity("data/gfx/test.png", 1);
    ptr0->setDialogue(dialogue_options);
    Entity *ptr = new Entity("data/gfx/test.png", 1);
    ptr->setDialogue(dialogue_options);

    ptr0->setPosition(200, 300);
    ptr->setPosition(300, 400);

    this->entityManager->AddEntity("npc1", ptr0);
    this->entityManager->AddEntity("npc2", ptr);

    // Add cheeses
    this->entityManager->AddEntity("test", new Entity("data/gfx/cheese.png", 0));
    this->entityManager->AddEntity("test0", new Entity("data/gfx/cheese.png", 0));
    this->entityManager->AddEntity("test1", new Entity("data/gfx/cheese.png", 0));
    this->entityManager->Get("test")->velocity.x = 0.5;
    this->entityManager->Get("test")->setPosition(sf::Vector2f(50, 500));
    this->entityManager->Get("test0")->setPosition(sf::Vector2f(50, 300));
    this->entityManager->Get("test1")->velocity.x = 1.0f;
    this->entityManager->Get("test1")->setPosition(sf::Vector2f(50, 800));
    if (!this->font.loadFromFile("../src/arial.ttf")) {
        std::cerr << "Error loading font" << std::endl;
        return;
    }


    // Load Map
    this->map = new Map();
    MapLoad(this->map, "data/map/level1.json");
    this->entityManager->SetMap(this->map);

    this->camera = new Camera(window);


    // Load Player
    this->player = new Player(this->entityManager, this->map, this->camera, 100, 100);
    this->entityManager->AddEntity("Player", this->player);

    
    // Load Weapon
    this->weapon = new Weapon(this->map, 120, 90);
    this->entityManager->AddEntity("Weapon", this->weapon);

    this->entityManager->AddEntity("test", new Entity("data/gfx/test.png", 1));
    this->entityManager->AddEntity("test0", new Entity("data/gfx/test.png", 1));
    this->entityManager->Get("test")->setPosition(sf::Vector2f(50, 50));
    this->entityManager->Get("test0")->setPosition(sf::Vector2f(50, 300));

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

    // copy position and velocity from player to weapon
    this->weapon->setPosition(this->player->getPosition());
    this->weapon->velocity = this->player->velocity;
    
    this->weapon->Update(window, inputManager, timeElapsed);
    this->entityManager->Update();
    this->map->CheckCollision(this->player);

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
    this->camera->Update(window, this->map, sf::Vector2f(this->player->getPosition().x, this->player->getPosition().y));
}

void MainGame::Render(sf::RenderWindow* window) {
    this->map->RenderGround(window);
    this->entityManager->Render(window, this->camera);
    this->map->RenderAbove(window);

    sf::Vector2f viewCenter = this->camera->GetView().getCenter();
    sf::Vector2f viewSize = this->camera->GetView().getSize();

    sf::Vector2f topLeft(viewCenter.x - viewSize.x / 2, viewCenter.y - viewSize.y / 2);

    sf::Text text;
    text.setFont(this->font);
    text.setString("Coins: " + std::to_string(this->coinCount));
    text.setCharacterSize(50);
    text.setFillColor(sf::Color::White);
    text.setPosition(topLeft.x + 10.f, topLeft.y + 10.f);

    window->draw(text);
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