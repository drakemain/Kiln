#pragma once

#include "Entity.h"

class Sprite : public Entity {
public:
  Sprite();
  Sprite(class Texture*);

  class SpriteComponent* getComponent();

private:
  class SpriteComponent* sprite;
};