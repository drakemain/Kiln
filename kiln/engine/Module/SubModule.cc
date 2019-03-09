#include "SubModule.h"
#include "KilnModule.h"
#include "kiln/engine/Classes/Entity/headers/Entity.h"
#include "kiln/engine/Classes/Components/headers/EventComponent.h"
#include "kiln/engine/Classes/Components/headers/SpriteComponent.h"
#include "kiln/engine/Core/headers/LayerManager.h"

SubModule::SubModule(class KilnModule* mod): module(mod) {
  this->layers = new LayerManager();
}

SubModule::~SubModule() {
  delete this->layers;
}

void SubModule::render(SDL_Renderer* renderer) {
  for (size_t i = 0; i < this->layers->getLayerCount(); ++i) {
    const std::vector<Entity*>* layer = this->layers->getLayer(i);

    for (Entity* ent : *layer) {
      ent->render(renderer);
    }
  }
}

void SubModule::tick(float detlaTime) {
  for (Entity* entity : this->entities) {
    entity->tick(detlaTime);
  }

  this->layers->update();
}

void SubModule::start() {
  for (Entity* entity : this->entities) {
    entity->start();
  }
}

AssetDependencies SubModule::getRequiredAssets() const {
  return this->assetDependencies;
}

void SubModule::setEntityLayer(Entity* entity, size_t layer) {
  this->layers->moveToLayer(entity, layer);
}

void SubModule::adjustEntityLayer(Entity* entity, int layers) {
  
}

void SubModule::registerEntity(Entity* entity) {
  this->entities.push_back(entity);

  bool registeredSprite = false;

  // Better solution? If renderable, add to layer manager
  std::vector<Component*> comps;
  entity->getComponents(comps);
  for (Component* comp : comps) {
    if (!registeredSprite) {
      if (dynamic_cast<SpriteComponent*>(comp)) {
        this->layers->add(entity);
        registeredSprite = true;
      }
    }

    EventComponent* eventComponent = dynamic_cast<EventComponent*>(comp);
    if (eventComponent) {
      this->module->bindEventComponent(eventComponent);
    }
  }
}

LayerManager* SubModule::getLayerManager() {
  return this->layers;
}