#include "../headers/LayerManager.h"

LayerManager::LayerManager() {
  std::unordered_map<Entity*, size_t> map = std::unordered_map<Entity*, size_t>();
  this->entityMap = std::make_unique<std::unordered_map<Entity*, size_t>>(map);
}

void LayerManager::add(class Entity* entity, size_t layer = 0) {
  if (!entity) { return; }

  if (!this->entityMap->empty()) {
    if (this->entityMap->find(entity) != this->entityMap->end()) {
      this->requestedUpdates.push({entity, layer});
    }
  }

  printf("Entity %p was added to layer %d of %p.\n", entity, (int)layer, this);
}

void LayerManager::remove(class Entity* entity) {
  if (this->entityMap->find(entity) != this->entityMap->end()) {
    this->removeFromLayer(entity);
    this->entityMap->erase(entity);
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
  this->entityMap->at(entity) = _layer;
}

void LayerManager::removeFromLayer(Entity* entity) {
  if (this->entityMap->find(entity) == this->entityMap->end()) {
    return;
  }

  int currentLayer = this->entityMap->at(entity);
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