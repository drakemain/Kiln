#include "ModuleSub.h"
#include "kiln/engine/Classes/headers/Entity.h"
#include "kiln/engine/Classes/Components/headers/SpriteComponent.h"
#include "kiln/engine/Core/headers/LayerManager.h"

ModuleSub::ModuleSub(class KilnModule* mod): module(mod) {
  this->layers = new LayerManager();
}

void ModuleSub::render(SDL_Renderer* renderer) {
  // printf("RENDER Layers: %d\n", (int)this->layers->getLayerCount());
  for (size_t i = 0; i < this->layers->getLayerCount(); ++i) {
    // printf("\tLayer %d\n", (int)i);
    const std::vector<Entity*>* layer = this->layers->getLayer(i);

    for (Entity* ent : *layer) {
      // printf("\t\tRender: %p\n", ent);
      ent->render(renderer);
    }
  }
}

void ModuleSub::tick(float detlaTime) {
  for (Entity* entity : this->entities) {
    entity->tick(detlaTime);
  }

  this->layers->update();
}

AssetDependencies ModuleSub::getRequiredAssets() const {
  return this->assetDependencies;
}

void ModuleSub::setEntityLayer(Entity* entity, size_t layer) {
  this->layers->moveToLayer(entity, layer);
}

void ModuleSub::adjustEntityLayer(Entity* entity, int layers) {
  
}

void ModuleSub::registerEntity(Entity* entity) {
  this->entities.push_back(entity);

  // Better solution? If renderable, add to layer manager
  for (Component* comp : entity->getComponents()) {
    if (dynamic_cast<SpriteComponent*>(comp)) {
      this->layers->add(entity);
      break;
    }
  }
}

LayerManager* ModuleSub::getLayerManager() {
  return this->layers;
}