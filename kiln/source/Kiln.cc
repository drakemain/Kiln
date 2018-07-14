#include "kiln/headers/Kiln.h"
#include <iostream>
#include "kiln/headers/Sprite.h"

bool Kiln::init() {
  std::cout << "INIT" << std::endl;

  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    std::cout << "Failed to init SDL:\n\t" << SDL_GetError() << std::endl;
    return false;
  }

  int imgFlags = IMG_INIT_JPG|IMG_INIT_PNG;

  if ((IMG_Init(imgFlags) & imgFlags) != imgFlags) {
    std::cout << "Failed to init SDL_Image:\n\t" << IMG_GetError() << "\n\t" << SDL_GetError() << std::endl;
    return false;
  }

  if (!this->windowManager.init()) {
    return false;
  }

  return true;
}

void Kiln::run() {
  std::cout << "RUN" << std::endl;

  Sprite sprite;
  if(!sprite.loadImage("kiln/assets/img/sprite-test.jpg")) {
    this->isRunning = false;
  }

  while(isRunning) {
    if (this->inputManager.poll()) {
      this->eventHandler(this->inputManager.getEvent());
    }

    SDL_RenderClear(this->getBaseRenderer());
    SDL_RenderCopy(this->getBaseRenderer(), sprite.getTexture(), NULL, sprite.getContainer());
    SDL_RenderPresent(this->getBaseRenderer());
  }
}

void Kiln::cleanup() {
  std::cout << "CLEANUP" << std::endl;

  this->windowManager.cleanup();

  IMG_Quit();
  SDL_Quit();
}

/* Helper Functions */
void Kiln::eventHandler(SDL_Event* event) {
  switch(event->type) {
    case SDL_QUIT:
    this->isRunning = false; break;
  }
}