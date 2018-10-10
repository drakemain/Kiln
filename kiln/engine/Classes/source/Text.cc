#include "../headers/Text.h"
#include <iostream>

Text::Text(std::string text, TTF_Font* font, SDL_Color color, SDL_Renderer* renderer)
: TextBase(text, font, color, renderer) {
  this->text = text;
  this->font = font;
  this->color = color;
  this->draw(renderer);
}

Text::~Text() {}

void Text::render(SDL_Renderer* renderer) {
  SDL_Rect container;
  container.w = this->getDimensions().w;
  container.h = this->getDimensions().h;
  container.x = this->getWorldPosition().x;
  container.y = this->getWorldPosition().y;

  SDL_RenderCopyEx(
    renderer,
    this->getTexture(),
    NULL,
    &container,
    this->getRotationDegrees(),
    NULL,
    SDL_FLIP_NONE  
  );
}