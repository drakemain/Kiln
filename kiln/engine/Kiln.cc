#include "Kiln.h"
#include "kiln/src/InitState.h"
#include <iostream>

Kiln::Kiln() {}

bool Kiln::init() {
  std::cout << "INIT" << std::endl;

  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    std::cerr << "Failed to init SDL:\n\t" << SDL_GetError() << std::endl;
    return false;
  }

  if (!this->coreManagement.windowManager.init()) {
    return false;
  }

  if (!this->coreManagement.assetManager.init(this->coreManagement.windowManager.getRenderer())) {
    return false;
  }

  this->coreManagement.state.pushForce(std::unique_ptr<State>(new InitState(this->coreManagement)));
  
  return true;
}

void Kiln::loadAssets() {
  
}

void Kiln::run() {
  std::cout << "RUN" << std::endl;

  if (this->coreManagement.state.empty()) {
    std::cout << "Empty state!" << std::endl;
  }

  Uint32 runTime;
  unsigned int lastTime = 0;
  float deltaTime = 0;

  while(isRunning && !this->coreManagement.state.empty()) {
    runTime = SDL_GetTicks();
    deltaTime = runTime - lastTime;
    lastTime = runTime;

    this->coreManagement.state.update();
    this->coreManagement.state.getActiveState()->tick(deltaTime);

    if (this->coreManagement.inputManager.poll()) {
      this->eventHandler(this->coreManagement.inputManager.getEvent());
    }
    

  }
}

void Kiln::cleanup() {
  std::cout << "CLEANUP" << std::endl;

  this->coreManagement.windowManager.cleanup();

  SDL_Quit();
}

/* Helper Functions */
void Kiln::eventHandler(SDL_Event* event) {
  switch(event->type) {
    case SDL_QUIT:
    std::cout << "QUIT EVENT" << std::endl;
    this->isRunning = false; break;
  }
}