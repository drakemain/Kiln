#include "../headers/Button.h"
#include "kiln/engine/Classes/Components/headers/ClickComponent.h"
#include "kiln/engine/Classes/Components/headers/SpriteComponent.h"
#include "kiln/engine/Classes/Components/headers/TextComponent.h"
#include <iostream>

Button::Button(class Texture* texture) {
  this->click = new ClickComponent(this);
  this->sprite = new SpriteComponent(this, texture);
}

Button::Button(class Texture* texture, std::string text, TTF_Font* font, SDL_Color color, SDL_Renderer* renderer) {
  this->click = new ClickComponent(this);
  this->sprite = new SpriteComponent(this, texture);
  this->text = new TextComponent(
    this,
    text,
    font,
    renderer,
    color
  );
}

Button::~Button() {}

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