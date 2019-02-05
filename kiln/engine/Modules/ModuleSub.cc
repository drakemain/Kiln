#include "ModuleSub.h"
#include "kiln/engine/Classes/headers/Entity.h"
#include "kiln/engine/Classes/Components/headers/SpriteComponent.h"
#include "kiln/engine/Core/headers/LayerManager.h"

ModuleSub::ModuleSub(class KilnModule* mod): module(mod) {
  this->layers = new LayerManager();
}

void ModuleSub::render(SDL_Renderer* renderer) {
  for (Entity* entity : this->entities) {
    entity->render(renderer);
  }
}

void ModuleSub::tick(float detlaTime) {
  for (Entity* entity : this->entities) {
    entity->tick(detlaTime);
  }
}

AssetDependencies ModuleSub::getRequiredAssets() const {
  return this->assetDependencies;
}

void ModuleSub::registerEntity(Entity* entity) {
  this->entities.push_back(entity);

  // Better solution? If renderable, add to layer manager
  for (Component* comp : entity->getComponents()) {
    if (dynamic_cast<SpriteComponent*>(comp)) {
      this->layers->add(entity, 0);
      break;
    }
  }
}