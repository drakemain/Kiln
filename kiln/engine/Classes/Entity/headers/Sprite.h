#pragma once

#include "Entity.h"

class Sprite : public Entity {
public:
  Sprite();
  Sprite(class Texture*);

  class SpriteComponent* getComponent();

  struct Dim getDimesions() const;

private:
  class SpriteComponent* sprite;
};