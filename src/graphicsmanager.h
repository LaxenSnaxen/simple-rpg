#ifndef _GRAPHICSMANAGER_H
#define _GRAPHICSMANAGER_H

#include <unordered_map>
#include <SFML/Graphics.hpp>

class GraphicsManager {
public:
    GraphicsManager();
    ~GraphicsManager();

    static GraphicsManager *get_instance();

    // Load a texture from a file (cached).
    // If the texture was loaded previously, returns that same texture.
    sf::Texture *get_texture(std::string const &filename);

    sf::Texture *get_empty_texture();

private:
    std::unordered_map<std::string, sf::Texture *> textures;
    sf::Texture *empty_texture;
};

#endif
