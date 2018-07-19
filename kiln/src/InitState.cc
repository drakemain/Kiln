#include "InitState.h"
#include "kiln/engine/Definitions/Colors.h"
#include <iostream>

InitState::InitState(CoreManagement& coreManagement)
: coreManagement(coreManagement) {}

InitState::~InitState() {
  this->cleanup();
}

void InitState::init() {
  SDL_Renderer* renderer = this->coreManagement.windowManager.getRenderer();
  Texture* testTexture = this->coreManagement.assetManager.loadTexture("kiln/assets/img/sprite-test.jpg", "SpriteTest", renderer);

  std::cout << "INIT STATE INIT" << std::endl;

  if (testTexture) {
    std::cout << "Loading sprite." << std::endl;
    this->testSprite = new Sprite(testTexture);
    std::cout << "Sprite loaded." << std::endl;
  } else {
    std::cout << "Fetched bad texture!" << std::endl;
  }
  
  std::cout << "INIT STATE INIT COMPLETE" << std::endl;
}

void InitState::cleanup() {
  delete this->testSprite;
}

void InitState::pause() {}

void InitState::resume() {}

void InitState::handleEvents() {}

void InitState::tick(float deltaTime) {
  this->uptime += deltaTime;
  this->render();
}

void InitState::render() {
  SDL_Renderer* renderer = this->coreManagement.windowManager.getRenderer();
  this->testSprite->render(renderer);
}