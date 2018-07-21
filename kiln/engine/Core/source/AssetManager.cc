#include "../headers/AssetManager.h"
#include <iostream>

Texture* Texture::placeholder = nullptr;

AssetManager::AssetManager() {
  std::cout << "Asset manager has been constructed." << std::endl;
}

AssetManager::~AssetManager() {
  std::cout << "Cleaning up managed assets..." << std::endl;

  std::map<std::string, Texture*>::iterator textureItr;
  std::map<std::string, TTF_Font*>::iterator fontItr;
  std::map<std::string, Mix_Music*>::iterator musicItr;
  std::map<std::string, Mix_Chunk*>::iterator soundIter;

  for (textureItr = this->TextureMap.begin(); textureItr != this->TextureMap.end(); ++textureItr) {
    delete textureItr->second;
    std::cout << "\tTEXTURE: " << textureItr->first << std::endl;
  }

  for (fontItr = this->FontMap.begin(); fontItr != this->FontMap.end(); ++fontItr) {
    TTF_CloseFont(fontItr->second);
    std::cout << "\tFONT: " << fontItr->first << std::endl;
  }

  for (musicItr = this->MusicMap.begin(); musicItr != this->MusicMap.end(); ++musicItr) {
    Mix_FreeMusic(musicItr->second);
    std::cout << "\tCleaned up MUSIC: " << musicItr->first << std::endl;
  }

  for (soundIter = this->SoundMap.begin(); soundIter != this->SoundMap.end(); ++soundIter) {
    Mix_FreeChunk(soundIter->second);
    std::cout << "\tSOUND: " << soundIter->first << std::endl;
  }

  IMG_Quit();
  TTF_Quit();
  Mix_Quit();

  std::cout << " Done." << std::endl;
}

bool AssetManager::init(SDL_Renderer* renderer) {
  std::cout << "\tSetting up asset manager." << std::endl;

  int imgFlags = IMG_INIT_JPG|IMG_INIT_PNG;

  if ((IMG_Init(imgFlags) & imgFlags) != imgFlags) {
    std::cerr << "Failed to init SDL_image:\n\t" << IMG_GetError() << "\n\t" << SDL_GetError() << std::endl;
    return false;
  }

  if (TTF_Init() == -1) {
    std::cerr << "Failed to init SDL_ttf:\n\t" << TTF_GetError() << std::endl;
    return false;
  }

  if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
    std::cerr << "Failed to init SDL_mixer:\n\t" << Mix_GetError() << std::endl;
    return false;
  }

  Texture::placeholder = this->loadTexture("kiln/assets/img/placeholder-texture.jpg", renderer);

  std::cout << "\tAsset Manager ready!" << std::endl;

  return true;
}

/* Texture */
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
  // TODO: handle key DNE
  std::cout << "\tLoaded textures: " << (int)this->TextureMap.size() << std::endl;
  return this->TextureMap[name];
}

void AssetManager::unloadTexture(std::string name) {
  delete this->TextureMap[name];
  this->TextureMap.erase(name);
}

/* Font */
TTF_Font* AssetManager::loadFont(std::string path, std::string name) {
  TTF_Font* font = TTF_OpenFont(path.c_str(), 28);

  if (font == NULL) {
    std::cerr << "\tFailed to load font: " << name << ".\n\t\t" << TTF_GetError() << std::endl;
    return nullptr;
  }

  std::cout << "\tLoaded font: " << name << std::endl;
  this->FontMap[name] = font;

  return font;
}

TTF_Font* AssetManager::loadFont(std::string path) {
  TTF_Font* font = TTF_OpenFont(path.c_str(), 28);

  if (font == NULL) {
    std::cerr << "\tFailed to load font:" << ".\n\t\t" << TTF_GetError() << std::endl;
    return nullptr;
  }

  std::cout << "\tLoaded an unmanaged font." << std::endl;

  return font;
}

TTF_Font* AssetManager::fetchFont(std::string name) {
  // TODO: handle key DNE
  return this->FontMap[name];
}

void AssetManager::unloadFont(std::string name) {
  TTF_CloseFont(this->FontMap[name]);
  this->FontMap.erase(name);
}

/* Music */
Mix_Music* AssetManager::loadMusic(std::string path, std::string name) {
  Mix_Music* music = Mix_LoadMUS(path.c_str());

  if (!music) {
    std::cerr << "\tFailed to load music: " << name << ".\n\t\t" << Mix_GetError() << std::endl;
    return nullptr;
  }

  std::cout << "\tLoaded music: " << name << std::endl;
  this->MusicMap[name] = music;
  return music;
}

Mix_Music* AssetManager::loadMusic(std::string path) {
  Mix_Music* music = Mix_LoadMUS(path.c_str());

  if (!music) {
    std::cerr << "\tFailed to load unamanged music." << ".\n\t\t" << Mix_GetError() << std::endl;
    return nullptr;
  }

  std::cout << "\tLoaded unmanaged music." << std::endl;
  return music;
}

Mix_Music* AssetManager::fetchMusic(std::string name) {
  // TODO: handle key DNE
  return this->MusicMap[name];
}

void AssetManager::unloadMusic(std::string name) {
  Mix_FreeMusic(this->MusicMap[name]);
  this->MusicMap.erase(name);
}


/* Sound */
Mix_Chunk* AssetManager::loadSound(std::string path, std::string name) {
  Mix_Chunk* sound = Mix_LoadWAV(path.c_str());

  if (!sound) {
    std::cerr << "\tFailed to load sound: " << name << ".\n\t\t" << Mix_GetError() << std::endl;
    return nullptr;
  }

  std::cout << "\tLoaded sound: " << name << std::endl;
  this->SoundMap[name] = sound;
  return sound;
}

Mix_Chunk* AssetManager::loadSound(std::string path) {
  Mix_Chunk* sound = Mix_LoadWAV(path.c_str());

  if (!sound) {
    std::cerr << "\tFailed to load sound: " << ".\n\t\t" << Mix_GetError() << std::endl;
    return nullptr;
  }

  std::cout << "\tLoaded unmanaged sound: " << std::endl;
  return sound;
}

Mix_Chunk* AssetManager::fetchSound(std::string name) {
  // TODO: handle key DNE
  return this->SoundMap[name];
}

void AssetManager::unloadSound(std::string name) {
  Mix_FreeChunk(this->SoundMap[name]);
  this->SoundMap.erase(name);
}