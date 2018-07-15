#include "kiln/headers/AssetManager.h"
#include <iostream>

AssetManager::AssetManager() {
  std::cout << "Asset manager has been constructed." << std::endl;
}

AssetManager::~AssetManager() {
  std::map<std::string, Sprite*>::iterator itr;

  for (itr = this->SpriteMap.begin(); itr != this->SpriteMap.end(); ++itr) {
    delete itr->second;
  }

  std::cout << "Asset manager has been deleted!" << std::endl;
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