#pragma once

#include <SDL_events.h>

#include <unordered_map>
#include <vector>
#include <functional>

class InputManager {
  using Action = std::function<void()>;

public:
  InputManager();
  ~InputManager();

  bool poll();

  const union SDL_Event* getLastEvent() const;

  void bind(SDL_Keycode, Action);
  void bindInputComponents();
  void handleInputs();

private:
  void handleKeys();
  void registerKeyDown();
  void registerKeyUp();

  SDL_Event buffer;
  std::unordered_map<SDL_Keycode, Action> bindings;
  const Uint8* keyStates;
  int keyCount;

  // There is probably a better way to handle this
  std::vector<SDL_Keycode> pressedKeys;
};