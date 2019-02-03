#include "../headers/LayerManager.h"

LayerManager::LayerManager() {}

void LayerManager::add(class Entity* entity, size_t layer = 0) {
  if (this->entityMap.find(entity) != this->entityMap.end()) {
    this->requestedUpdates.push({entity, layer});
  }
}

void LayerManager::remove(class Entity* entity) {
  if (this->entityMap.find(entity) != this->entityMap.end()) {
    this->removeFromLayer(entity);
    this->entityMap.erase(entity);
  }
}

void LayerManager::moveToLayer(class Entity* entity, size_t layer) {
  this->requestedUpdates.push({entity, layer});
}

void LayerManager::update() {
  while(!this->requestedUpdates.empty()) {
    std::pair<class Entity*, size_t> update = this->requestedUpdates.front();
    this->removeFromLayer(update.first);
    
    this->insertToLayer(update.first, update.second);
  }
}

size_t LayerManager::getLayerCount() const {
  return this->layers.size();
}

void LayerManager::createLayer() {
  this->layers.push_back(std::make_unique<std::vector<Entity*>>());
}

void LayerManager::insertToLayer(Entity* entity, size_t layer) {
  size_t _layer = layer%this->getLayerCount();
  this->layers[_layer]->push_back(entity);
  this->entityMap[entity] = _layer;
}

void LayerManager::removeFromLayer(Entity* entity) {
  if (this->entityMap.find(entity) == this->entityMap.end()) {
    return;
  }

  int currentLayer = entityMap[entity];
  auto it = this->layers[currentLayer]->begin();

  while (it < this->layers[currentLayer]->end()) {
    if (*it == entity) {
      this->layers[currentLayer]->erase(it);
      break;
    }

    ++it;
  }

  if (this->layers[currentLayer]->empty()) {
    this->layers.erase(this->layers.begin() + currentLayer);
  }
}