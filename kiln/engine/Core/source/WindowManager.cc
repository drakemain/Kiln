#include "../headers/WindowManager.h"
#include "../headers/ConfigLoader/WindowConfig.h"
#include <SDL.h>
#include <iostream>

bool WindowManager::init(const WindowConfig& conf) {
  std::cout << "\tSetting up window manager." << std::endl;

  this->title = conf.title.c_str();
  this->WIDTH = conf.w;
  this->HEIGHT = conf.h;

  this->window = SDL_CreateWindow(this->title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, this->WIDTH, this->HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);

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

void WindowManager::setResolution(const Dim newRes) {
  this->WIDTH = newRes.w;
  this->HEIGHT = newRes.h;

  if (this->window) {
    SDL_SetWindowSize(this->window, this->WIDTH, this->HEIGHT);
  } else {
    std::cout << "Attempted to set resolution while there is no window!" << std::endl;
  }
}

void WindowManager::setFrameLimit(float frameLimit) {
  this->FRAME_LIMIT = frameLimit;
  this->MIN_FRAME_TIME = 1000.f / frameLimit;
}