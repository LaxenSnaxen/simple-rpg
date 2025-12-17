#include <iostream>

#include "state/maingame.h"

InputManager inputManager;
GameStateManager gameState;

int main()
{
    std::cout << "Hello World!" << std::endl;

    std::string gameName = "Hamzes Cheesy ÄventyrsQuest 2: Johan Ostman Deluxe Edition";
    unsigned int windowStyle = sf::Style::Titlebar | sf::Style::Close;
    sf::ContextSettings settings;
    settings.antialiasingLevel = 16;

    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), gameName, windowStyle, settings);
    window.clear(sf::Color(0, 0, 0));
    window.display();
    //window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);

    gameState.SetWindow(&window);
    gameState.SetState(new MainGame());

    sf::Clock fpsTimer;
    sf::Clock timer;
    sf::Time timeElapsed;

    // Run the program as long as the window is open
    while (window.isOpen()) {
        // Check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event)) {
            // Close window : exit
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                window.close();
            }
            /*
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::P) {
                    for (int i = 0; i < 100; i++) {
                        for (int j = 0; j < 100; j++) {
                            std::cout << map->collision->data[i][j] << std::endl;
                        }
                    }
                }
                }
            }
            */
            // Fullscreen crashes the game
            // Enter fullscreen mode : key combination : Alt+Enter
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Return) {
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt)) {
                        if (windowStyle == sf::Style::Fullscreen) {
                            windowStyle = sf::Style::Titlebar | sf::Style::Close;
                        }
                        else {
                            windowStyle = sf::Style::Fullscreen;
                            
                            
                            
                        }

                        

                        window.create(sf::VideoMode::getDesktopMode(), gameName, windowStyle, settings);
                        window.setVerticalSyncEnabled(true);
                    }
                }
            }
        }

        window.clear(sf::Color(72, 152, 72));

        gameState.Update();
        gameState.Render();

        window.display();

        timeElapsed = timer.getElapsedTime();
        if (timeElapsed.asSeconds() > 1)
        {
            // Display current FPS in window title
            timeElapsed = fpsTimer.getElapsedTime();
            int fps = 1000000 / timeElapsed.asMicroseconds();
            window.setTitle(gameName + " - fps: " + std::to_string(fps));

            timer.restart();
        }

        fpsTimer.restart();
    }

    return 0;
}

