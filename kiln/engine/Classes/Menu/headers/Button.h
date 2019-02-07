#pragma once
#include "kiln/engine/Classes/Entity/headers/Entity.h"
#include "SDL_ttf.h"
#include <functional>

class Button : public Entity {
public:
  Button(class Texture* texture);
  Button(class Texture* texture, std::string text, TTF_Font* font, SDL_Color color, SDL_Renderer* renderer);
  ~Button();

  virtual void scale(float scale) override;

  class TextComponent* getTextComponent();

  bool checkWasClicked(ICoordinate clickPos);

  void bindAction(std::function<void()> func);

private:
  void setClickBounds();

  class ClickComponent* click = nullptr;
  class SpriteComponent* sprite = nullptr;
  class TextComponent* text = nullptr;
};