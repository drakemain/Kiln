#pragma once

#include "Component.h"

class EventComponent : public Component {
public:
  virtual void handleEvent(union SDL_Event&) = 0;
};