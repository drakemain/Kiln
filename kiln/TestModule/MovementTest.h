#include "kiln/engine/Classes/headers/Sprite.h"
#include "kiln/engine/Classes/Components/headers/MovementComponent.h"

class MovableSprite : public Sprite {
public:
  MovableSprite(Texture* texture): Sprite(texture), movement(this) {}

  void setVelocity(float x, float y) {this->movement.setVelocity(x, y);}
  Velocity getVelocity() const { return movement.getVelocity();}

  void tick(float deltaTime) {this->movement.tick(deltaTime);}

private:
  MovementComponent movement;
};