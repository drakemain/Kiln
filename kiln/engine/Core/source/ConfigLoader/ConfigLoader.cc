#include "../../headers/ConfigLoader/ConfigLoader.h"

void ConfigLoader::load(const char* filePath) {
  try {
    this->config = cpptoml::parse_file(filePath);
  } catch(cpptoml::parse_exception& e) {
    printf("CONFIG ERR: %s\n", e.what());
  }

  this->configWindow();
}

std::string ConfigLoader::title() const {
  return this->config->get_as<std::string>("title").value_or("Kiln");
}

const WindowConfig& ConfigLoader::window() const {
  return this->windowConfig;
}

void ConfigLoader::configWindow() {
  this->windowConfig.title = this->title();

  auto windowConf = this->config->get_table("window");

  this->windowConfig.w = windowConf->get_as<unsigned int>("dim_w").value_or(640);
  this->windowConfig.h = windowConf->get_as<unsigned int>("dim_h").value_or(480);
}