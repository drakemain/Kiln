#include "../headers/WindowManager.h"
#include <iostream>

bool WindowManager::init() {
  std::cout << "\tSetting up window manager." << std::endl;

  this->window = SDL_CreateWindow("Kiln", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, this->WIDTH, this->HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);

  if (this->window == NULL) {
    std::cerr << "Failed to init window: " << SDL_GetError() << std::endl;
    return false;
  }

  this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);

  if (this->renderer == NULL) {
    std::cerr << "Failed to init renderer: " << SDL_GetError() << std::endl;
    return false;
  }
  
  this->setFrameLimit(this->FRAME_LIMIT);

  std::cout << "\tWindow Manager ready!" << std::endl;

  return true;
}

void WindowManager::cleanup() {
  SDL_DestroyRenderer(this->renderer);
  SDL_DestroyWindow(this->window);
}

SDL_Window* WindowManager::getWindow() const {
  return this->window;
}

SDL_Renderer* WindowManager::getRenderer() const {
  return this->renderer;
}

Dim WindowManager::getResolution() const {
  return {this->WIDTH, this->HEIGHT};
}

void WindowManager::setFrameLimit(float frameLimit) {
  this->FRAME_LIMIT = frameLimit;
  this->MIN_FRAME_TIME = 1000.f / frameLimit;
}