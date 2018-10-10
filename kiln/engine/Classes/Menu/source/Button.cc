#include "../headers/Button.h"
#include "kiln/engine/Classes/Components/headers/ClickComponent.h"
#include "kiln/engine/Classes/Components/headers/UIComponent.h"
#include "kiln/engine/Classes/Components/headers/TextComponent.h"
#include <iostream>

Button::Button(Texture* texture)
: Sprite(texture) {
  this->click = new ClickComponent(this);
  this->UI = new UIComponent(this);
}

Button::Button(Texture* texture, std::string text, TTF_Font* font, SDL_Color color, SDL_Renderer* renderer)
: Sprite(texture) {
  std::cout << "Button const" << std::endl;
  this->click = new ClickComponent(this);
  this->UI = new UIComponent(this);
  this->text = new TextComponent(
    this,
    text,
    font,
    color,
    renderer
  );
  std::cout << "Button const compl" << std::endl;
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

TextComponent* Button::getTextComponent() {
  if (!this->text) {
    std::cout << "BUTTON HAS NOT INITIALIZED TEXT" << std::endl;
  }

  return this->text;
}

void Button::render(SDL_Renderer* renderer) {
  Sprite::render(renderer);
  if (this->text) {
    this->text->render(renderer);
  }
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