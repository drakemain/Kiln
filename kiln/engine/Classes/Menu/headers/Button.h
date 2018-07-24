#pragma once
#include "kiln/engine/Classes/headers/Sprite.h"
#include "kiln/engine/Classes/Components/headers/ClickComponent.h"

class Button : public Sprite {
public:
  Button(Texture* texture);
  Button(Dim dimensions);

  void render(SDL_Renderer* renderer);

  bool wasClicked(ICoordinate clickPos);

private:
  ClickComponent click;
};