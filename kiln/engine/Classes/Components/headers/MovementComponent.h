#pragma once

#include "Component.h"
#include "kiln/engine/Utils/Math/Vector.h"
#include "kiln/engine/Utils/Math/Scalar.h"

#define Vec KMath::Vector<float>

class MovementComponent : public Component {
public:
  MovementComponent(Entity* owner);

  void setVelocity(Vec velocity);
  void setVelocity(float x, float y);
  void accelerate(const Vec& vector);

  Vec getVelocity() const;
  float getSpeed();

  virtual void start() override {};
  virtual void tick(float deltaTime) override;
private:
  void updatePosition(float deltaTime);

  // pixels per second
  Vec velocity;
  float maxVelocity = 5.f;
};