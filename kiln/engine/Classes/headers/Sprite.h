#pragma once
#include <SDL.h>
#include "kiln/engine/Classes/Base/headers/SpriteBase.h"
#include "Entity.h"

class Sprite : public Entity, public SpriteBase {
public:
  Sprite(Texture* texture);
  Sprite();

  virtual void tick(float deltaTime) override {}
  virtual void start() override {}

  void centerInWindow(unsigned int xBound, unsigned int yBound) override;

  void render(SDL_Renderer* renderer) override;
};