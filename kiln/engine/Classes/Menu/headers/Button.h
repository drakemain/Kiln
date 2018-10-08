#pragma once
#include "kiln/engine/Classes/headers/Sprite.h"
#include <functional>

class Button : public Sprite {
public:
  Button(Texture* texture);
  Button(Dim dimensions);
  ~Button();

  void render(SDL_Renderer* renderer);
  void ifClicked(ICoordinate clickPos);

  void bindAction(std::function<void()> func);

private:
  class ClickComponent* click;
  class UIComponent* UI;
};