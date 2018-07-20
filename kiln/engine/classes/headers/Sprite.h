#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include "Texture.h"
#include "Entity.h"

struct Dim {
  unsigned int w = 0;
  unsigned int h = 0;
};

class Sprite : public Entity {
public:
  Sprite(Texture* texture);
  Sprite();
  virtual ~Sprite();

  Dim getDimensions() const;

  void setWidth(unsigned int width);
  void setHeight(unsigned int height);

  void render(SDL_Renderer* renderer) const;

private:
  Dim dimensions;

protected:
  SDL_Texture* texture;
};