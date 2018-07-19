#include "../headers/AssetManager.h"
#include <iostream>

Texture* Texture::placeholder = nullptr;

AssetManager::AssetManager() {
  std::cout << "Asset manager has been constructed." << std::endl;
}

AssetManager::~AssetManager() {
  std::map<std::string, Texture*>::iterator spriteItr;
  std::map<std::string, TTF_Font*>::iterator fontItr;

  for (spriteItr = this->TextureMap.begin(); spriteItr != this->TextureMap.end(); ++spriteItr) {
    delete spriteItr->second;
  }

  for (fontItr = this->FontMap.begin(); fontItr != this->FontMap.end(); ++fontItr) {
    TTF_CloseFont(fontItr->second);
  }

  IMG_Quit();
  TTF_Quit();

  std::cout << "Asset manager has been deleted!" << std::endl;
}

bool AssetManager::init(SDL_Renderer* renderer) {
  std::cout << "\tSetting up asset manager." << std::endl;

  int imgFlags = IMG_INIT_JPG|IMG_INIT_PNG;

  if ((IMG_Init(imgFlags) & imgFlags) != imgFlags) {
    std::cerr << "Failed to init SDL_Image:\n\t" << IMG_GetError() << "\n\t" << SDL_GetError() << std::endl;
    return false;
  }

  if (TTF_Init() == -1) {
    std::cerr << "Failed to init SDL_TTF:\n\t" << TTF_GetError() << std::endl;
    return false;
  }

  Texture::placeholder = this->loadTexture("kiln/assets/img/placeholder-texture.jpg", renderer);

  std::cout << "\tAsset Manager ready!" << std::endl;

  return true;
}

Texture* AssetManager::loadTexture(std::string path, std::string name, SDL_Renderer* renderer) {
  Texture* texture = new Texture();
  bool success = texture->create(path, renderer);

  if (success) {
    std::cout << "\tLoaded texture: " << name << std::endl;
    this->TextureMap[name] = texture;
    return texture;
  }
  
  std::cerr << "\tFailed to create texture!\n\t\t" << SDL_GetError() << std::endl;
  
  if (Texture::placeholder) {
    return Texture::placeholder;
  } else {
    return nullptr;
  }
}

Texture* AssetManager::loadTexture(std::string path, SDL_Renderer* renderer) {
  Texture* texture = new Texture();
  bool success = texture->create(path, renderer);

  if (success) {
    std::cout << "\tLoaded an unmanaged texture." << std::endl;
    return texture;
  }
  
  std::cerr << "\tFailed to create texture!\n\t\t" << SDL_GetError() << std::endl;
  
  if (Texture::placeholder) {
    return Texture::placeholder;
  } else {
    return nullptr;
  }
}

Texture* AssetManager::fetchTexture(std::string name) {
  std::cout << "Loaded textures: " << (int)this->TextureMap.size() << std::endl;
  return this->TextureMap[name];
}

void AssetManager::unloadTexture(std::string name) {
  delete this->TextureMap[name];
  this->TextureMap.erase(name);
}

TTF_Font* AssetManager::loadFont(std::string path, std::string name) {
  TTF_Font* font = TTF_OpenFont(path.c_str(), 28);

  if (font == NULL) {
    std::cerr << "\tFailed to load font " << name << ".\n\t\t" << TTF_GetError() << std::endl;
    return nullptr;
  }

  std::cout << "\tLoaded font: " << name << std::endl;
  this->FontMap[name] = font;

  return font;
}