#pragma once

#include <memory>
#include "lib/cpptoml/include/cpptoml.h"
#include "WindowConfig.h"
#include "AssetConfig.h"

class ConfigLoader {
public:
  void load(const char* filePath);

  std::string title() const;

  const WindowConfig& window() const;
  const AssetConfig& asset() const;

private:
  void configWindow();
  void configAsset();

  std::shared_ptr<cpptoml::table> config;
  WindowConfig windowConfig;
  AssetConfig assetConfig;
};