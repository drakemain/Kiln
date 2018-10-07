#pragma once
#include "kiln/engine/States/headers/State.h"
#include <string>
#include <vector>

typedef std::vector<std::pair<std::string, std::string>> AssetList;

struct AssetDependencies {
  AssetList textures;
  AssetList fonts;
  AssetList sounds;
  AssetList music;
};

class ModuleSub : public State {
public:
  ModuleSub(class KilnModule* mod) : module(mod) {}
  class KilnModule* module;
  AssetDependencies getRequiredAssets() const { return this->assetDependencies; }

protected:
  AssetDependencies assetDependencies;
};