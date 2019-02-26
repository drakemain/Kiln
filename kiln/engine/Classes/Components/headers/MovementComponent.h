#pragma once

#include "Component.h"
#include "kiln/engine/Utils/Math/Vector.h"
#include "kiln/engine/Utils/Math/Scalar.h"

#define Vec KMath::Vector::Vector<float>

enum Direction {
  Up,
  Down,
  Left,
  Right
};

class MovementComponent : public Component {
public:
  MovementComponent();
  MovementComponent(Entity* owner);

  void consumeDirection(Vec vector);

  Vec getVelocity() const;

  virtual void start() override {};
  virtual void tick(float deltaTime) override;
private:
  void updatePosition(float deltaTime);

  // pixels per second
  Vec velocity = {0.f, 0.f};
  Vec accumulatedDirection = {0.f, 0.f};
  float maxVelocity = 500.f;
  float maxAcceleration = 500.f;
};