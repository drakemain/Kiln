#include "../headers/InputManager.h"

bool InputManager::poll() {
  if (SDL_PollEvent(&this->eventBuffer) == 0) {
    return false;
  } else {
    return true;
  }
}

SDL_Event* InputManager::getEvent() {
  return &this->eventBuffer;
}