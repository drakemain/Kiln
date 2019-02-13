#include "../headers/EventManager.h"
#include "kiln/engine/Classes/Components/headers/EventComponent.h"
#include <SDL_events.h>

EventManager::EventManager() {}

void EventManager::registerComponent(EventComponent* component) {
  this->components.push_back(component);
}

void EventManager::addEvent(const SDL_Event* event) {
  this->events.push(event);
}

void EventManager::handleEvents() {
  // TODO: needs better runtime solution
  while(!this->events.empty()) {
    const SDL_Event* event = this->events.front();
    this->events.pop();

    for (EventComponent* component : this->components) {
      component->handleEvent(*event);
    }
  }
}