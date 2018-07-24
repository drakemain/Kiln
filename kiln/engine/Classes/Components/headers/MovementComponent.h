#include "Component.h"
#include "kiln/engine/Utils/Math/Vector.h"

#define Velocity KMath::Vector<float>

class MovementComponent : public Component {
public:
  MovementComponent(Entity* owner);

  void setVelocity(Velocity velocity);
  void setVelocity(float x, float y);

  Velocity getVelocity() const;

  void tick(float deltaTime);
private:
  void updatePosition(float deltaTime);

  // pixels per second
  Velocity velocity;
};