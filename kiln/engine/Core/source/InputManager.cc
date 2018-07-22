#include "../headers/InputManager.h"

bool InputManager::poll() {
  if (SDL_PollEvent(&this->eventBuffer) == 0) {
    return false;
  } else {
    this->updateCursorPosition(&this->eventBuffer);
    this->updateCursorClickedPosition(&this->eventBuffer);
    
    return true;
  }
}

SDL_Event* InputManager::getEvent() {
  return &this->eventBuffer;
}

Coordinate InputManager::getCursorPosition() const {
  return this->cursorPosition;
}

Coordinate InputManager::getCursorClickedPosition() const {
  return this->clickPosition;
}

void InputManager::updateCursorPosition(SDL_Event* event) {
  if (event->type == SDL_MOUSEMOTION) {
    SDL_GetMouseState(&this->cursorPosition.x, &this->cursorPosition.y);
  }
}

void InputManager::updateCursorClickedPosition(SDL_Event* event) {
  if (event->type == SDL_MOUSEBUTTONDOWN) {
    SDL_GetMouseState(&this->clickPosition.x, &this->clickPosition.y);
  }
}