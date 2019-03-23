#include "SubModule.h"
#include "KilnModule.h"
#include "kiln/engine/Classes/Entity/headers/Entity.h"
#include "kiln/engine/Classes/Components/headers/EventComponent.h"
#include "kiln/engine/Classes/Components/headers/SpriteComponent.h"
#include "kiln/engine/Core/headers/SpriteManager.h"
#include "lib/kilnlog/include/KilnLog.h"

SubModule::SubModule(class KilnModule* mod): module(mod) {
  this->spriteManager = new SpriteManager();
}

SubModule::~SubModule() {
  delete this->spriteManager;
}

void SubModule::render(SDL_Renderer* renderer) {
  this->spriteManager->render(renderer);
}

void SubModule::tick(float detlaTime) {
  for (Entity* entity : this->entities) {
    entity->tick(detlaTime);
  }
}

void SubModule::start() {
  KLog.put(KLOG_INF, "Submodule is starting.");

  for (Entity* entity : this->entities) {
    entity->start();
  }
}

AssetDependencies SubModule::getRequiredAssets() const {
  return this->assetDependencies;
}

void SubModule::registerEntity(Entity* entity) {
  this->entities.push_back(entity);

  // Will be added if entity contains SpriteComponent
  this->spriteManager->add(entity);
}