#pragma once
#include <SDL.h>
#include "kiln/engine/Utils/headers/Coordinate.h"

class InputManager {
public:
  // check event queue and move the next event into eventBuffer
  bool poll();

  // TODO: Stop using pointer to member
  SDL_Event* getEvent();

  ICoordinate getCursorPosition() const;
  ICoordinate getCursorClickedPosition() const;


private:
  void updateCursorPosition(SDL_Event* event);
  void updateCursorClickedPosition(SDL_Event* event);
  
  ICoordinate cursorPosition;
  ICoordinate clickPosition;
  SDL_Event eventBuffer;
};