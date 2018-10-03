#pragma once
#include <unordered_map>
#include <iostream>
#include "kiln/engine/States/headers/StateMachine.h"
#include "kiln/engine/Core/headers/AssetManager.h"
#include "kiln/engine/Core/headers/WindowManager.h"
#include "kiln/engine/Classes/headers/Sprite.h"
#include "ModuleSub.h"

class KilnModule {
public:
  KilnModule() {}
  ~KilnModule() {
    for (std::pair<std::string, Sprite*> sprite : this->spriteMap) {
      delete sprite.second;
    }
  }

  virtual bool init() {
    return true;
  }

  virtual void start() {}
  virtual void handleEvent(SDL_Event* event) {
    this->subState.getActiveState()->handleEvent(event);
  }
  virtual void tick(float deltaTime) {
    std::cout << "Module Tick" << std::endl;
    this->subState.getActiveState()->tick(deltaTime);
  }
  virtual void render() {
    this->subState.getActiveState()->render();
  }

  void bind(AssetManager* assets) { this->assets = assets; }
  void bind(WindowManager* window) { this->window = window; }

  Sprite* createSprite(std::string path, std::string name) {
    Texture* texture = this->assets->loadTexture(path, name, this->window->getRenderer());
    Sprite* newSprite = new Sprite(texture);
    this->spriteMap[name] = newSprite;
    return newSprite;
  }

  Sprite* fetchSprite(std::string name) {
    return this->spriteMap[name];
  }

  void updateSubState() { this->subState.update(); }

  bool hasSub() { return !this->subState.empty(); }

  AssetManager* assets;
  WindowManager* window;
  std::unordered_map<std::string, Sprite*> spriteMap;
  StateMachine subState;
};