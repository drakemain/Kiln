#pragma once

#include <unordered_map>
#include <queue>
#include <memory>

class LayerManager {
public:
  LayerManager();
  ~LayerManager();

  void add(class Entity*);
  void remove(class Entity*);
  void moveToLayer(class Entity*, size_t);
  void moveUpLayer(class Entity*);
  void moveDownLayer(class Entity*);
  void moveToTop(class Entity*);
  void moveToNewTop(class Entity*);
  void moveToBottom(class Entity*);
  void update();
  size_t getLayerCount() const;

  const std::vector<class Entity*>* getLayer(size_t) const;

private:
  void adjustLayer(class Entity*, int);
  void createLayer();
  void insertToLayer(class Entity*, size_t);
  void insertLayer(int layer);
  void removeFromLayer(class Entity*);

  std::vector<std::unique_ptr<std::vector<class Entity*>>>* layers;
  std::unordered_map<class Entity*, size_t>* entityMap;
  std::queue<std::pair<class Entity*, size_t>>* requestedUpdates;

  size_t maxLayers = 10;
};