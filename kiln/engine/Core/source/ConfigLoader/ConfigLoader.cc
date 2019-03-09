#include "../../headers/ConfigLoader/ConfigLoader.h"
#include "lib/kilnlog/include/KilnLog.h"
#include <SDL_image.h>

void ConfigLoader::load(const char* filePath) {
  try {
    KLog.put(KLOG_INF, "Fetching config from %s", filePath);
    this->config = cpptoml::parse_file(filePath);
  } catch(cpptoml::parse_exception& e) {
    KLog.put(KLOG_WAR, "Failed to fetch config. %s. Using default values.", e.what());
  }

  this->configWindow();
  this->configAsset();
  this->configLogs();
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

const LogConfig& ConfigLoader::logs() const {
  return this->logConfig;
}

void ConfigLoader::configWindow() {
  this->windowConfig.title = this->title();

  auto windowConf = this->config->get_table("window");
  auto rendererConf = windowConf->get_table("renderer");

  this->windowConfig.w = windowConf->get_as<unsigned int>("dim_w").value_or(640);
  this->windowConfig.h = windowConf->get_as<unsigned int>("dim_h").value_or(480);

  if (rendererConf->get_as<bool>("vsync").value_or(true)) {
    this->windowConfig.renderFlags = this->windowConfig.renderFlags | SDL_RENDERER_PRESENTVSYNC;
  }

  if (rendererConf->get_as<bool>("hwaccel").value_or(false)) {
    this->windowConfig.renderFlags = this->windowConfig.renderFlags | SDL_RENDERER_ACCELERATED;
  }
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

void ConfigLoader::configLogs() {
  auto table = this->config->get_table("logs");
  
  this->logConfig.level = table->get_as<int>("level").value_or(1);
  this->logConfig.silent = table->get_as<bool>("silent").value_or(false);
  this->logConfig.flushOnStart = table->get_as<bool>("flushOnStart").value_or(true);
}