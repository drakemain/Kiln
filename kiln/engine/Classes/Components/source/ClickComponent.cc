#include "../headers/ClickComponent.h"

ClickComponent::ClickComponent(Entity* owner)
: Component(owner) {

}

bool ClickComponent::wasClicked(ICoordinate mouseLocation, unsigned int boundingWidth, unsigned int boundingHeight) {
  FCoordinate ownerLocation = this->getOwner()->getWorldPosition();

  bool insideX = (mouseLocation.x > ownerLocation.x)
    && (mouseLocation.x < (ownerLocation.x + (int)boundingWidth));
  bool insideY = (mouseLocation.y > ownerLocation.y)
    && (mouseLocation.y < (ownerLocation.y + (int)boundingHeight));

  return insideX && insideY;
}