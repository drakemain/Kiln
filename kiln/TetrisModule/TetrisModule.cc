#include "TetrisModule.h"
#include "subs/headers/init.h"

bool TetrisModule::init() {
  KilnModule::init();

  std::cout << "Kiln loaded Tetris!" << std::endl;

  this->loadSub(new InitSub(this));
  
  return true;
}

void TetrisModule::start() {
  KilnModule::start();
}

void TetrisModule::handleEvent(SDL_Event* event) {
  KilnModule::handleEvent(event);
}

void TetrisModule::tick(float deltaTime) {
  KilnModule::tick(deltaTime);
}

void TetrisModule::render() {
  KilnModule::render();
}