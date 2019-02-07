#pragma once

#include <unordered_map>
#include <SDL_events.h>

using func = void(*)(void);

class InputManager {
public:
  // check event queue adds to queue
  bool poll();

  const union SDL_Event* getLastEvent() const;

  void bind(uint32_t, func);
  void handleEvent();

private:
  SDL_Event buffer;
  std::unordered_map<uint32_t, func> bindings; 
};