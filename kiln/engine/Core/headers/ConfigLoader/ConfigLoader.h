#pragma once

#include <memory>
#include "lib/cpptoml/include/cpptoml.h"
#include "WindowConfig.h"

class ConfigLoader {
public:
  void load(const char* filePath);

  std::string title() const;

  const WindowConfig& window() const;

private:
  void configWindow();

  std::shared_ptr<cpptoml::table> config;
  WindowConfig windowConfig;
  
};