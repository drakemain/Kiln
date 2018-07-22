#pragma once
#include "Component.h"

class ClickComponent : public Component {
public:
  ClickComponent(Entity* owner);

  bool wasClicked(Coordinate mouseLocation, unsigned int boundingWidth, unsigned int boundingHeight);
};