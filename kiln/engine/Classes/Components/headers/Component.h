#pragma once

#include "kiln/engine/Utils/headers/Coordinate.h"

// enum Alignment {
//   TopLeft,
//   TopRight,
//   TopCenter,
//   CenterLeft,
//   CenterRight,
//   Center,
//   BottomLeft,
//   BottomRight,
//   BottomCenter
// };

class Component {
public:
  friend class Entity;
  Component(class Entity* owner);
  Component();
  virtual ~Component();

  void setRelativePosition(FCoordinate pos);
  void setRelativePosition(int x, int y);
  // void setRelativePosition(Position position);

  FCoordinate getRelativePosition() const;
  FCoordinate getWorldPosition() const;

  void updatePosition();

  virtual void start() = 0;
  virtual void tick(float deltaTime) = 0;

  class Entity* getOwner() const;

private:
  Entity* owner;

  void setWorldPosition();

  class FCoordinate worldPosition;
  class FCoordinate relativePosition;
};