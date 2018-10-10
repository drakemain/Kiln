#pragma once
#include "TextBase.h"
#include "Entity.h"
#include <SDL_ttf.h>
#include <string>

class Text : public Entity, public TextBase {
public:
  Text(std::string text, TTF_Font* font, SDL_Color color, SDL_Renderer* renderer);
  ~Text();
  
  void render(SDL_Renderer* renderer);

private:
  std::string text;
  TTF_Font* font;
  SDL_Color color;
  
  bool wasModified = false;
};