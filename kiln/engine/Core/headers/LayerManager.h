#pragma once

#include <unordered_map>
#include <queue>
#include <memory>

class LayerManager {
public:
  LayerManager();

  void add(class Entity*, size_t);
  void remove(class Entity*);
  void moveToLayer(class Entity*, size_t);
  void update();
  size_t getLayerCount() const;

private:
  void createLayer();
  void insertToLayer(class Entity*, size_t);
  void insertLayer(int layer);
  void removeFromLayer(class Entity*);

  std::vector<std::unique_ptr<std::vector<class Entity*>>> layers;
  std::unordered_map<class Entity*, size_t> entityMap;
  std::queue<std::pair<class Entity*, size_t>> requestedUpdates;

  size_t maxLayers = 10;
};