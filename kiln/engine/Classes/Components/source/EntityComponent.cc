#include "kiln/engine/Classes/Components/headers/EntityComponent.h"
#include <iostream>

EntityComponent::EntityComponent(Entity* owner)
: Component(owner) {
  std::cout << "Entity Comp Const" << std::endl;
  this->setWorldPosition(owner->getWorldPosition());
  owner->bindComponent(this);
}

void EntityComponent::updatePosition() {
  std::cout << "Entity Component Pos Being Updated." << std::endl;

  this->setWorldPosition(
    this->getOwner()->getWorldPosition()
    + this->relativePosition
  );
}