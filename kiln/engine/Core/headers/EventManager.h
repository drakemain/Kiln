#pragma once

#include <queue>
#include <memory>

class EventManager {
public:
  EventManager();

  void registerComponent(class EventComponent*);
  void addEvent(union SDL_Event* event);
  void handleEvents();

  std::queue<union SDL_Event*> events;
  std::vector<class EventComponent*> components;
};