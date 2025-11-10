#include "player.h"

Player::Player(EntityManager* entityManager, Map *map, Camera *camera, float x, float y) {
    this->entityManager = entityManager;
    this->map = map;
    this->camera = camera;

    this->Load("data/gfx/player.png");
    this->setPosition(x, y);
    this->speed = 0.00015f;
    // Stamina initialization
    this->maxStamina = 3.0f;
    stamina = maxStamina;
}

// Variables for sprinting and stamina system
bool isResting = false;
float restTimer = 5.0f;
float sprintMultiplier = 1.0f;


void Player::Update(sf::RenderWindow* window, InputManager inputManager, int timeElapsed) {
    float speed = this->speed * timeElapsed;
    // Sprint ability
    // Original speed is multiplied with a factor while sprinting 
    // Player loses 1 stamina per second while sprinting
    // Player regains 1 stamina per second while not sprinting
    // When player depletes stamina, they must rest for 5 seconds

    // Flight ability
    // Player can also use stamina to fly
    // Flight is slower but you can move over trees and other things

    float sprintMultiplier = 1.0f;
    
    if(isResting == true){
        // Decrease rest timer in seconds
        restTimer -= 1.0f/60.0f;
        if(restTimer <= 0.0f){
            isResting = false;
            stamina = maxStamina;
            restTimer = 5.0f;
        }

    } else if(inputManager.IsPressed(InputManager::SprintAbility) && stamina > 0.0f && isResting == false){
        sprintMultiplier = 3.0f;
        // Drain stamina per second using actual frame time
        stamina -= 1.0f/60.0f;
        
        if(stamina <= 0.0f){
            // Start forced rest when stamina depletes
            stamina = 0.0f;
            isResting = true;
            restTimer = 5.0f;
            sprintMultiplier = 1.0f;
        }
    } else if(inputManager.IsPressed(InputManager::FlightAbility) && stamina > 0.0f && isResting == false){
        sprintMultiplier = 2.0f;

        stamina -= 1.0f/60.0f;
        
        if(stamina <= 0.0f){
            // Start forced rest when stamina depletes
            stamina = 0.0f;
            isResting = true;
            restTimer = 5.0f;
            sprintMultiplier = 1.0f;
        }
    } else {
        // Regenerate stamina while not sprinting and not resting
        stamina += 1.0f/60.0f;
        if(stamina > maxStamina){
            stamina = maxStamina;
        }
    }

    speed = speed * sprintMultiplier;
    // Update player velocity
    this->velocity.x = inputManager.IsPressed(InputManager::Right) * speed -
                       inputManager.IsPressed(InputManager::Left) * speed;
    this->velocity.y = inputManager.IsPressed(InputManager::Down) * speed -
                       inputManager.IsPressed(InputManager::Up) * speed;

    // Set correct speed on diagonal movement
    if((this->velocity.x == speed || this->velocity.x == -speed)
    && (this->velocity.y == speed || this->velocity.y == -speed)) {
        this->velocity.x *= .75;
        this->velocity.y *= .75;
    }
    
}

float Player::GetSpeed() {
    return this->speed;
}

Player::~Player()
{

}
