#include "../headers/Button.h"
#include "kiln/engine/Classes/Components/headers/ClickComponent.h"
#include "kiln/engine/Classes/Components/headers/UIComponent.h"

Button::Button(Texture* texture)
: Sprite(texture) {
  this->click = new ClickComponent(this);
  this->UI = new UIComponent(this);
}

Button::Button(Dim dimensions) {
  this->click = new ClickComponent(this);
  this->UI = new UIComponent(this);
  this->setWidth(dimensions.w);
  this->setHeight(dimensions.h);
}

Button::~Button() {
  delete this->click;
  delete this->UI;
}

void Button::render(SDL_Renderer* renderer) {
  Sprite::render(renderer);
}

void Button::ifClicked(ICoordinate clickPos) {
  Dim dimensions = this->getDimensions();
  if (this->click->wasClicked(clickPos, dimensions.w, dimensions.h)) {
    this->click->onClick();
  }
}

void Button::bindAction(std::function<void()> func) {
  this->click->bindAction(func);
}