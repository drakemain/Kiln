#include "../headers/InputManager.h"
#include <SDL.h>
#include <iostream>

bool InputManager::poll() {
  return SDL_PollEvent(&this->buffer) != 0;
}

const SDL_Event* InputManager::getLastEvent() const {
  return &this->buffer;
}

void InputManager::bind(uint32_t keyCode, void(*action)(void)) {
  std::cout << "Bound " << keyCode << "." << std::endl;
  this->bindings[keyCode] = action; 
}

void InputManager::handleEvent() {
  auto binding = this->bindings.find(this->buffer.key.keysym.sym);

  if (binding != this->bindings.end()) {
    binding->second();
  }

  // while (!this->eventQueue.empty()) {
  //   SDL_Event* event = this->eventQueue.front();
  //   this->eventQueue.empty();

  //   auto binding = this->bindings.find(event->key.keysym.sym);

  //   if (binding != this->bindings.end()) {
  //     func action = binding->second;
  //     action();
  //   }

  //   // if (this->bindings.find())
  // }
}