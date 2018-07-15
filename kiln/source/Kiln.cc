#include "kiln/headers/Kiln.h"
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

void Kiln::run() {
  std::cout << "RUN" << std::endl;

  TTF_Font* font = this->assetManager.loadFont("kiln/assets/font/RobotoMono-Regular.ttf", "Roboto");

  if (!font) {
    this->isRunning = false;
  }

  SDL_Surface* textSurface = TTF_RenderText_Solid(font, "Test Text", SDL_Color{0, 0, 0, 0xFF});
  SDL_Texture* textTexture = SDL_CreateTextureFromSurface(this->getBaseRenderer(), textSurface);

  SDL_FreeSurface(textSurface);

  while(isRunning) {
    if (this->inputManager.poll()) {
      this->eventHandler(this->inputManager.getEvent());
    }

    SDL_SetRenderDrawColor(this->getBaseRenderer(), 0x0, 0x88, 0xFF, 0xFF);
    SDL_RenderClear(this->getBaseRenderer());
    SDL_RenderCopy(this->getBaseRenderer(), textTexture, NULL, NULL);
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