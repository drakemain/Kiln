#include "../headers/InputComponent.h"

void InputComponent::bind(SDL_Keycode key, std::function<void()> action) {
  printf("BIND ON INPUT COMP\n");
  InputComponent::bindings->push({key, action});
}