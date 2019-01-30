#pragma once
#include "kiln/engine/Classes/Base/headers/TextBase.h"
#include "Entity.h"
#include <SDL_ttf.h>
#include <string>

class Text : public Entity, public TextBase {
public:
  Text(std::string text, TTF_Font* font, SDL_Color color, SDL_Renderer* renderer);
  ~Text();

  virtual void tick(float deltaTime) override {}
  virtual void start() override {}
  
  void render(SDL_Renderer* renderer);
};