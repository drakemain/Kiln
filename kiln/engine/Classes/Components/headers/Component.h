#pragma once
#include "kiln/engine/Classes/headers/Entity.h"

class Component {
public:
  Component(Entity* owner);
  Component();
  virtual ~Component();

  void setRelativePosition(ICoordinate pos);
  void setRelativePosition(int x, int y);

  ICoordinate getRelativePosition() const;
  ICoordinate getWorldPosition() const;

  void updatePosition();

  virtual void start() = 0;
  virtual void tick(float deltaTime) = 0;

protected:
  Entity* getOwner() const;

private:
  Entity* owner;

  void setWorldPosition();

  class ICoordinate worldPosition;
  class ICoordinate relativePosition;
};