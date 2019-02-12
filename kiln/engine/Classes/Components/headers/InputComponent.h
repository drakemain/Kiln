#pragma once

#include "Component.h"
#include <queue>
#include <SDL_keycode.h>
#include <functional>

class InputComponent : public Component {
public:
  static std::queue<std::pair<SDL_Keycode, std::function<void()>>>* bindings;

  InputComponent(): Component() {};
  ~InputComponent() {}

  virtual void start() override {};
  virtual void tick(float deltaTime) override {};

  void bind(SDL_Keycode, std::function<void()>);
};