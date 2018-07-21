#include "../headers/Component.h"

Component::Component(Entity* owner)
: owner(owner) {

}

Entity* Component::getOwner() const {
  return this->owner;
}

Component::Component() {}

Component::~Component() {}