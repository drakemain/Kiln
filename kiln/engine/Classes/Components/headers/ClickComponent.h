#pragma once
#include "EventComponent.h"
#include "kiln/engine/Classes/Entity/headers/Entity.h"
#include <SDL_events.h>
#include <functional>
#include <iostream>

class ClickComponent : public EventComponent {
public:
  ~ClickComponent() override {}
  bool wasClicked(FCoordinate mouseLocation, unsigned int boundingWidth, unsigned int boundingHeight);

  void setWidthBound(int w) { this->wBound = w; }

  void setHeightBound(int h) { this->hBound = h; }

  void bindAction(std::function<void()> action) { this->action = action; }
  void onClick() { this->action(); }

  void tick(float deltaTime) override {}
  void start() override {}

  void handleEvent(const SDL_Event& event) override;

private:
  // Need lambda for click action
  std::function<void()> action = [](){};
  int wBound;
  int hBound;
};