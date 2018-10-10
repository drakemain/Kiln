#include "../headers/Component.h"

Component::Component(Entity* owner)
: owner(owner) {

}

Component::Component() {}

Component::~Component() {}

Entity* Component::getOwner() const {
  return this->owner;
}
