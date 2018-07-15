#include "Kiln.h"
#include <iostream>

bool Kiln::init() {
  std::cout << "INIT" << std::endl;

  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    std::cerr << "Failed to init SDL:\n\t" << SDL_GetError() << std::endl;
    return false;
  }

  if (!this->assetManager.init()) {
    return false;
  }

  if (!this->windowManager.init()) {
    return false;
  }

  return true;
}

void Kiln::loadAssets() {
  this->assetManager.loadTexture("kiln/assets/img/sprite-test.jpg", "SpriteTest");
  this->assetManager.loadTexture("kiln/assets/img/sprite-test2.jpg", "SpriteTest2");
}

void Kiln::run() {
  std::cout << "RUN" << std::endl;

  Sprite sprite;
  sprite.fromTexture(this->assetManager.fetchTexture("SpriteTest"));
  Sprite sprite2;
  sprite2.fromTexture(this->assetManager.fetchTexture("SpriteTest"));

  sprite.setWidth(320);
  sprite2.setWidth(320);
  sprite2.setPosition(320, 0);

  // TTF_Font* font = this->assetManager.loadFont("kiln/assets/font/RobotoMono-Regular.ttf", "Roboto");

  // if (!font) {
  //   this->isRunning = false;
  // }

  while(isRunning) {
    if (this->inputManager.poll()) {
      this->eventHandler(this->inputManager.getEvent());
    }

    SDL_SetRenderDrawColor(this->getBaseRenderer(), 0x0, 0x88, 0xFF, 0xFF);
    SDL_RenderClear(this->getBaseRenderer());
    sprite.render();
    sprite2.render();
    // SDL_RenderCopy(this->getBaseRenderer(), textTexture, NULL, NULL);
    SDL_RenderPresent(this->getBaseRenderer());
  }
}

void Kiln::cleanup() {
  std::cout << "CLEANUP" << std::endl;

  this->windowManager.cleanup();

  SDL_Quit();
}

/* Helper Functions */
void Kiln::eventHandler(SDL_Event* event) {
  switch(event->type) {
    case SDL_QUIT:
    this->isRunning = false; break;
  }
}