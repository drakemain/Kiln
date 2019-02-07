#include "../headers/Button.h"
#include "kiln/engine/Classes/Components/headers/ClickComponent.h"
#include "kiln/engine/Classes/Components/headers/SpriteComponent.h"
#include "kiln/engine/Classes/Components/headers/TextComponent.h"
#include <iostream>

Button::Button(class Texture* texture) {
  this->click = new ClickComponent();
  this->sprite = new SpriteComponent(texture);

  this->bindComponent(click);
  this->bindComponent(sprite);

  this->setClickBounds();
}

Button::Button(class Texture* texture, std::string text, TTF_Font* font, SDL_Color color, SDL_Renderer* renderer) {
  this->click = new ClickComponent();
  this->sprite = new SpriteComponent(texture);
  this->text = new TextComponent(
    text,
    font,
    renderer,
    color
  );

  this->bindComponent(this->click);
  this->bindComponent(this->sprite);
  this->bindComponent(this->text);

  this->setClickBounds();
}

Button::~Button() {}

void Button::scale(float scale) {
  Entity::scale(scale);

  this->setClickBounds();
}

TextComponent* Button::getTextComponent() {
  if (!this->text) {
    std::cout << "BUTTON HAS NOT INITIALIZED TEXT" << std::endl;
  }

  return this->text;
}

bool Button::checkWasClicked(ICoordinate clickPos) {
  Dim dimensions = this->sprite->getDimensions();
  bool result = false;

  if (this->click->wasClicked(clickPos, dimensions.w, dimensions.h)) {
    result = true;
    this->click->onClick();
  }

  return result;
}

void Button::bindAction(std::function<void()> func) {
  this->click->bindAction(func);
}

void Button::setClickBounds() {
  this->click->setWidthBound(this->sprite->getDimensions().w);
  this->click->setHeightBound(this->sprite->getDimensions().h);
}