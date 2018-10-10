#pragma once
#include "kiln/engine/Classes/headers/Entity.h"
#include "Component.h"

class EntityComponent : public Entity, public Component {
public:
  EntityComponent(Entity* owner);

  void updatePosition();

private:
  FCoordinate relativePosition;
};