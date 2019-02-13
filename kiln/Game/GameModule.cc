#include "GameModule.h"
#include "subs/headers/init.h"

bool GameModule::init() {
  KilnModule::init();

  std::cout << "Kiln loaded Tetris!" << std::endl;

  this->loadSub(new InitSub(this));
  
  return true;
}

void GameModule::start() {
  KilnModule::start();
}

void GameModule::handleEvent(const SDL_Event* event) {
  KilnModule::handleEvent(event);
}

void GameModule::tick(float deltaTime) {
  KilnModule::tick(deltaTime);
}

void GameModule::render() {
  KilnModule::render();
}