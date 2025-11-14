#include "maingame.h"
#include "entity.h"


void UpdateCollisions(Entity* entityA, Entity* entityB) {
    std::cout << "Collisions!" << std::endl;
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
    
    Entity *ptr0 = new Entity("data/gfx/test.png");
    ptr0->setDialogue(dialogue_options);
    Entity *ptr = new Entity("data/gfx/test.png");
    ptr->setDialogue(dialogue_options);
    // Add entities
    this->entityManager->AddEntity("test0", ptr0);
    this->entityManager->AddEntity("test", ptr);
    this->entityManager->Get("test0")->velocity.x = 0.5;
    this->entityManager->Get("test")->setPosition(sf::Vector2f(700, 1200)); // istället för 700 och 1200 så ska det vara korrdinaterna för trädet längst ner i högra hörnet
    this->entityManager->Get("test0")->setPosition(sf::Vector2f(50, 300));
    // Load Map
    this->map = new Map();
    MapLoad(this->map, "data/map/level1.json");

    // Load Camera
    this->camera = new Camera(window);

    // Load Player
    this->player = new Player(this->entityManager, this->map, this->camera, 100, 100);
    this->entityManager->AddEntity("Player", this->player);
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
