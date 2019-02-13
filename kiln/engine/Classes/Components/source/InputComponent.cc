#include "../headers/InputComponent.h"

void InputComponent::bind(SDL_Keycode key, std::function<void()> action) {
  InputComponent::bindings->push({key, action});
}