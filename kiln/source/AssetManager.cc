#include "kiln/headers/AssetManager.h"
#include <iostream>

AssetManager::AssetManager() {
  std::cout << "Asset manager has been constructed." << std::endl;
}

AssetManager::~AssetManager() {
  std::map<std::string, Sprite*>::iterator spriteItr;
  std::map<std::string, TTF_Font*>::iterator fontItr;

  for (spriteItr = this->SpriteMap.begin(); spriteItr != this->SpriteMap.end(); ++spriteItr) {
    delete spriteItr->second;
  }

  for (fontItr = this->FontMap.begin(); fontItr != this->FontMap.end(); ++fontItr) {
    TTF_CloseFont(fontItr->second);
  }

  IMG_Quit();
  TTF_Quit();

  std::cout << "Asset manager has been deleted!" << std::endl;
}

bool AssetManager::init() {
  int imgFlags = IMG_INIT_JPG|IMG_INIT_PNG;

  if ((IMG_Init(imgFlags) & imgFlags) != imgFlags) {
    std::cerr << "Failed to init SDL_Image:\n\t" << IMG_GetError() << "\n\t" << SDL_GetError() << std::endl;
    return false;
  }

  if (TTF_Init() == -1) {
    std::cerr << "Failed to init SDL_TTF:\n\t" << TTF_GetError() << std::endl;
    return false;
  }

  std::cout << "\tAsset Manager ready!" << std::endl;

  return true;
}

Sprite* AssetManager::loadSprite(std::string path, std::string name) {
  Sprite* sprite = new Sprite();
  bool success = sprite->load(path);

  if (success) {
    return this->SpriteMap[name] = sprite;
  }
  
  return nullptr;
}

Sprite* AssetManager::fetchSprite(std::string name) {
  return this->SpriteMap[name];
}

void AssetManager::unloadSprite(std::string name) {
  delete this->SpriteMap[name];
  this->SpriteMap.erase(name);
}

TTF_Font* AssetManager::loadFont(std::string path, std::string name) {
  TTF_Font* font = TTF_OpenFont(path.c_str(), 28);

  if (font == NULL) {
    std::cerr << "Failed to load font " << name << ".\n\t" << TTF_GetError() << std::endl;
    return nullptr;
  }

  this->FontMap[name] = font;

  return font;
}