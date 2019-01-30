#pragma once
#include "Component.h"
#include <functional>

class ClickComponent : public Component {
public:
  ClickComponent(Entity* owner);
  ~ClickComponent() override {}
  bool wasClicked(ICoordinate mouseLocation, unsigned int boundingWidth, unsigned int boundingHeight);

  void bindAction(std::function<void()> action) { this->action = action; }
  void onClick() { this->action(); }

  void tick(float deltaTime) override {}
  void start() override {}

  // Need lambda for click action
  std::function<void()> action = [](){};
};