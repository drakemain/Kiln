#include "../headers/InitState.h"
#include <iostream>

InitState::InitState(CoreManagement& coreManagement)
: coreManagement(coreManagement) {}

void InitState::init() {
  Texture* testTexture = this->coreManagement.assetManager.loadTexture("kiln/assets/img/sprite-test.jpg", "SpriteTest");
  this->coreManagement.assetManager.loadTexture("kiln/assets/img/sprite-test2.jpg", "SpriteTest2");

  std::cout << "INIT STATE INIT" << std::endl;

  if (testTexture) {
    std::cout << "Loading sprite." << std::endl;
    this->testSprite.fromTexture(testTexture);
    std::cout << "Sprite loaded." << std::endl;
  } else {
    std::cout << "Fetched bad texture!" << std::endl;
  }
  
  std::cout << "INIT STATE INIT COMPLETE" << std::endl;
}

void InitState::cleanup() {}

void InitState::pause() {}

void InitState::resume() {}

void InitState::handleEvents() {}

void InitState::tick(float deltaTime) {
  this->uptime += deltaTime;
  this->render();
}

void InitState::render() {
  SDL_RenderClear(this->getBaseRenderer());
  this->testSprite.render();
  SDL_RenderPresent(this->getBaseRenderer());
}