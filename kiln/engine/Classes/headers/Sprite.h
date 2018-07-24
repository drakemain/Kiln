#pragma once
#include <SDL.h>
#include "SpriteBase.h"
#include "Entity.h"

class Sprite : public Entity, public SpriteBase {
public:
  Sprite(Texture* texture);
  Sprite();

  void centerInWindow(unsigned int xBound, unsigned int yBound) override;

  void render(SDL_Renderer* renderer) const;
};