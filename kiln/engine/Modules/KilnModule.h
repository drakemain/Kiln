#pragma once
#include <unordered_map>
#include "kiln/engine/Core/headers/AssetManager.h"
#include "kiln/engine/Core/headers/WindowManager.h"
#include "kiln/engine/Classes/headers/Sprite.h"

class KilnModule {
public:
    KilnModule() {}
    ~KilnModule() {
        for (std::pair<std::string, Sprite*> sprite : this->spriteMap) {
            delete sprite.second;
        }
    }

    virtual bool init() = 0;
    virtual void start() = 0;
    virtual void cleanup() = 0;

    virtual void handleEvent(SDL_Event* event) = 0;
    virtual void tick(float deltaTime) = 0;
    virtual void render() = 0;

    void bind(AssetManager* assets) { this->assets = assets; }
    void bind(WindowManager* window) { this->window = window; }

protected:
    Sprite* createSprite(std::string path, std::string name) {
        Texture* texture = this->assets->loadTexture(path, name, this->window->getRenderer());
        Sprite* newSprite = new Sprite(texture);
        this->spriteMap[name] = newSprite;
        return newSprite;
    }

    Sprite* fetchSprite(std::string name) {
        return this->spriteMap[name];
    }

    AssetManager* assets;
    WindowManager* window;
    std::unordered_map<std::string, Sprite*> spriteMap; 
};