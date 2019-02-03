#include "ModuleSub.h"

ModuleSub::ModuleSub(class KilnModule* mod): module(mod) {}

AssetDependencies ModuleSub::getRequiredAssets() const {
  return this->assetDependencies;
}