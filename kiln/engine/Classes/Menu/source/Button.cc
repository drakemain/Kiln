#include "../headers/Button.h"

Button::Button(Texture* texture)
: Sprite(texture), click(this) {}

Button::Button(Dim dimensions) :
click(this) {
  this->setWidth(dimensions.w);
  this->setHeight(dimensions.h);
}

void Button::render(SDL_Renderer* renderer) {
  Sprite::render(renderer);
}

bool Button::wasClicked(Coordinate clickPos) {
  Dim dimensions = this->getDimensions();
  return this->click.wasClicked(clickPos, dimensions.w, dimensions.h);
} 