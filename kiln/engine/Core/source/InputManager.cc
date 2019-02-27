#include "../headers/InputManager.h"
#include "kiln/engine/Classes/Components/headers/InputComponent.h"
#include <SDL.h>

std::queue<std::pair<SDL_Keycode, std::function<void()>>>* InputComponent::bindings = new std::queue<std::pair<SDL_Keycode, std::function<void()>>>();

InputManager::InputManager() {
  this->keyStates = SDL_GetKeyboardState(&this->keyCount);
}

InputManager::~InputManager() {
  delete InputComponent::bindings;
}

bool InputManager::poll() {
  if (SDL_PollEvent(&this->buffer) == 0) {
    return false;
  }

  switch(this->buffer.type) {
    case SDL_KEYDOWN:
    this->registerKeyDown();
    break;

    case SDL_KEYUP:
    this->registerKeyUp();
    break;
  }

  return true;
}

const SDL_Event* InputManager::getLastEvent() const {
  return &this->buffer;
}

void InputManager::bind(Sint32 keyCode, Action action) {
  this->bindings[keyCode] = action; 
}

void InputManager::bindInputComponents() {
  printf("\tSetting up input components.\n");

  while(!InputComponent::bindings->empty()) {
    std::pair<SDL_Keycode, Action> binding = InputComponent::bindings->front();
    InputComponent::bindings->pop();

    this->bindings[binding.first] = binding.second;
  }
}

void InputManager::handleInputs() {
  this->handleKeys();
}

void InputManager::handleKeys() {
  // TODO: optimize
  // potentially slow if there are many bindings
  for (auto pair : this->bindings) {
    if (this->keyStates[SDL_GetScancodeFromKey(pair.first)]) {
      pair.second();
    }
  }
}

void InputManager::registerKeyDown() {
  this->pressedKeys.push_back(this->buffer.key.keysym.sym);
}

void InputManager::registerKeyUp() {
  for (auto itr = this->pressedKeys.begin(); itr != this->pressedKeys.end(); ++itr) {
    if (*itr == this->buffer.key.keysym.sym) {
      this->pressedKeys.erase(itr);
      break;
    }
  }
}