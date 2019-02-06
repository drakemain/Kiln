#include "../headers/Entity.h"
#include "../headers/Entity.h"
#include "../../Components/headers/Component.h"
#include "../../Components/headers/SpriteComponent.h"

Entity::Entity() {}

Entity::~Entity() {
  for (Component* comp : this->boundComponents) {
    delete comp;
  }
}

void Entity::start() {
  for (Component* comp : this->boundComponents) {
    comp->start();
  }
}

void Entity::tick(float deltaTime) {
  for (Component* comp : this->boundComponents) {
    comp->tick(deltaTime);
  }
}

ICoordinate Entity::getWorldPosition() const {
  return this->worldPosition;
}

void Entity::setWorldPosition(float x, float y) {
  this->worldPosition.x = x;
  this->worldPosition.y = y;

  this->updateComponentPositions();
}

void Entity::setWorldPosition(ICoordinate position) {
  this->worldPosition = position;
  this->updateComponentPositions();
}

void Entity::scale(float scale) {
  for (Component* comp : this->getComponents()) {
    SpriteComponent* sprite = dynamic_cast<SpriteComponent*>(comp);

    if (sprite) {
      sprite->setScale(scale);
    }
  }
}

void Entity::bindComponent(Component* component) {  
  if (component->getOwner() == this) {
    return;
  }

  component->owner = this;
  this->boundComponents.push_back(component);
}

void Entity::render(SDL_Renderer *renderer) {
  for (Component* comp : this->boundComponents) {
    SpriteComponent* sprite = dynamic_cast<SpriteComponent*>(comp);

    if (sprite) {
      sprite->render(renderer);
    }
  }
}

void Entity::updateComponentPositions() {
  for (Component* comp : this->boundComponents) {
    comp->updatePosition();
  }
}

void Entity::centerInWindow(unsigned int xBoundary, unsigned int yBoundary) {
  this->setWorldPosition(xBoundary / 2, yBoundary / 2);
}

std::vector<Component*> Entity::getComponents() {
  return this->boundComponents;
}

