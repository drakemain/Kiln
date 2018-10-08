#include "kiln/engine/Classes/Components/headers/UIComponent.h"
#include "kiln/engine/Classes/headers/Entity.h"

UIComponent::UIComponent(Entity* owner) : Component(owner) {}

void UIComponent::setAnchor(Anchor anchor) {
  this->anchor = anchor;
}

void UIComponent::reposition() {}