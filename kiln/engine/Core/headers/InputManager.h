#pragma once
#include <SDL.h>

class InputManager {
public:
  // check event queue and move the next event into eventBuffer
  bool poll();

  // TODO: Stop using pointer to member
  SDL_Event* getEvent();


private:
  SDL_Event eventBuffer;
};