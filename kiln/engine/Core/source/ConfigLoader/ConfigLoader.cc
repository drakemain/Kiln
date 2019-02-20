#include "../../headers/ConfigLoader/ConfigLoader.h"
#include <SDL_image.h>

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

const AssetConfig& ConfigLoader::asset() const {
  return this->assetConfig;
}

void ConfigLoader::configWindow() {
  this->windowConfig.title = this->title();

  auto windowConf = this->config->get_table("window");

  this->windowConfig.w = windowConf->get_as<unsigned int>("dim_w").value_or(640);
  this->windowConfig.h = windowConf->get_as<unsigned int>("dim_h").value_or(480);
}

void ConfigLoader::configAsset() {
  auto table = this->config->get_table("assets");

  auto imgfmt = table->get_table("imgfmt");
  // JPG support is opt-out
  if (imgfmt->get_as<bool>("jpg").value_or(true)) {
    this->assetConfig.imgfmt = this->assetConfig.imgfmt|IMG_INIT_JPG;
  }

  if (imgfmt->get_as<bool>("png").value_or(false)) {
    this->assetConfig.imgfmt = this->assetConfig.imgfmt|IMG_INIT_PNG;
  }

  if (imgfmt->get_as<bool>("tif").value_or(false)) {
    this->assetConfig.imgfmt = this->assetConfig.imgfmt|IMG_INIT_TIF;
  }

  if (imgfmt->get_as<bool>("webp").value_or(false)) {
    this->assetConfig.imgfmt = this->assetConfig.imgfmt|IMG_INIT_WEBP;
  }
}