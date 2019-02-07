#pragma once

#include <queue>
#include <memory>

class EventManager {
public:
  EventManager();

  void registerComponent(class EventComponent*);
  void addEvent(const union SDL_Event* event);
  void handleEvents();

  std::queue<const union SDL_Event*> events;
  std::vector<class EventComponent*> components;
};