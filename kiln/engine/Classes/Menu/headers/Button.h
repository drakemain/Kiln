#pragma once
#include "kiln/engine/Classes/headers/Sprite.h"
#include "SDL_ttf.h"
#include <functional>

class Button : public Sprite {
public:
  Button(Texture* texture);
  Button(Texture* texture, std::string text, TTF_Font* font, SDL_Color color, SDL_Renderer* renderer);
  Button(Dim dimensions);
  ~Button();

  class TextComponent* getTextComponent();

  void render(SDL_Renderer* renderer);
  void ifClicked(ICoordinate clickPos);

  void bindAction(std::function<void()> func);

private:
  class ClickComponent* click;
  class UIComponent* UI;
  class TextComponent* text;
};