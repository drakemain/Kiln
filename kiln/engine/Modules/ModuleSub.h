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
public:
  ModuleSub(class KilnModule* mod);

  AssetDependencies getRequiredAssets() const;

protected:
  class KilnModule* module;

protected:
  AssetDependencies assetDependencies;
};