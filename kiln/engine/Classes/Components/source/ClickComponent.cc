#include "../headers/ClickComponent.h"
#include "kiln/engine/Classes/Entity/headers/Entity.h"
#include <iostream>

bool ClickComponent::wasClicked(FCoordinate mouseLocation, unsigned int boundingWidth, unsigned int boundingHeight) {
  FCoordinate ownerLocation = this->getOwner()->getWorldPosition();

  bool insideX = (mouseLocation.x > ownerLocation.x)
    && (mouseLocation.x < (ownerLocation.x + (int)boundingWidth));
  bool insideY = (mouseLocation.y > ownerLocation.y)
    && (mouseLocation.y < (ownerLocation.y + (int)boundingHeight));

  return insideX && insideY;
}

void ClickComponent::handleEvent(const SDL_Event& event)  {
  if (event.type == SDL_MOUSEBUTTONDOWN) {
    int x, y;
    SDL_GetMouseState(&x, &y);

    if (this->wasClicked(FCoordinate::fromInt({x, y}), this->wBound, this->hBound)) {
      this->onClick();
    } 
  }
}