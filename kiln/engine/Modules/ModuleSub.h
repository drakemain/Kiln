#pragma once
#include "kiln/engine/States/headers/State.h"
#include <string>
#include <vector>

// filename, reference name
typedef std::pair<std::string, std::string> AssetPair;

struct AssetDependencies {
  std::vector<AssetPair> textures;
  // AssetPair, font size
  std::vector<std::pair<AssetPair, int>> fonts;
  std::vector<AssetPair> sounds;
  std::vector<AssetPair> music;
};

class ModuleSub : public State {
  friend class KilnModule;
public:
  ModuleSub(class KilnModule* mod);

protected:
  virtual void render(class SDL_Renderer* renderer) override;
  virtual void tick(float deltaTime) override;

public:
  AssetDependencies getRequiredAssets() const;

protected:
  void setEntityLayer(class Entity*, size_t layer);
  void adjustEntityLayer(class Entity*, int layer);
  void registerEntity(class Entity* entity);

  class KilnModule* module;
  AssetDependencies assetDependencies;

private:
  std::vector<class Entity*> entities;
  class LayerManager* layers;
};