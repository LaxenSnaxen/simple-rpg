#include "graphicsmanager.h"

GraphicsManager::GraphicsManager() {
    this->empty_texture = new sf::Texture;
}

GraphicsManager::~GraphicsManager() {

}

GraphicsManager *GraphicsManager::get_instance() {
    static GraphicsManager *gm = nullptr;

    if(gm == nullptr) {
        gm = new GraphicsManager();
    }

    return gm;
}

sf::Texture *GraphicsManager::get_texture(std::string const &filename) {
    sf::Texture *texture = nullptr;

    auto i = this->textures.find(filename);
    if(i == this->textures.end()) {
        // If the texture is NOT in the cache (loading for the first time)
        // then load it and store it in the cache.
        texture = new sf::Texture;
        texture->loadFromFile(filename);
        this->textures[filename] = texture;
    } else {
        // If the texture is in the cache, DON'T allocate a new one,
        // just take the one from the cache.
        texture = i->second;
    }

    return texture;
}

sf::Texture *GraphicsManager::get_empty_texture() {
    return this->empty_texture;
}