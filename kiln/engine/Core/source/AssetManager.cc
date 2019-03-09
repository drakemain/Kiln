#include "../headers/AssetManager.h"
#include "../headers/ConfigLoader/AssetConfig.h"
#include "kiln/engine/Core/headers/Texture.h"
#include "lib/kilnlog/include/KilnLog.h"

Texture* Texture::placeholder = nullptr;

AssetManager::AssetManager() {}

AssetManager::~AssetManager() {
  KLog.put(KLOG_DEB, "Cleaning up managed assets.");

  std::map<std::string, Texture*>::iterator textureItr;
  std::map<std::string, TTF_Font*>::iterator fontItr;
  std::map<std::string, Mix_Music*>::iterator musicItr;
  std::map<std::string, Mix_Chunk*>::iterator soundIter;

  for (textureItr = this->TextureMap.begin(); textureItr != this->TextureMap.end(); ++textureItr) {
    delete textureItr->second;
  }

  for (fontItr = this->FontMap.begin(); fontItr != this->FontMap.end(); ++fontItr) {
    TTF_CloseFont(fontItr->second);
    KLog.put(KLOG_INF, "FONT: %s", fontItr->first.c_str());
  }

  for (musicItr = this->MusicMap.begin(); musicItr != this->MusicMap.end(); ++musicItr) {
    Mix_FreeMusic(musicItr->second);
    KLog.put(KLOG_INF, "Cleaned up MUSIC: %s", musicItr->first.c_str());
  }

  for (soundIter = this->SoundMap.begin(); soundIter != this->SoundMap.end(); ++soundIter) {
    Mix_FreeChunk(soundIter->second);
    KLog.put(KLOG_INF, "SOUND: %s", soundIter->first.c_str());
  }

  IMG_Quit();
  TTF_Quit();
  Mix_Quit();
}

bool AssetManager::init(SDL_Renderer* renderer, const AssetConfig& config) {
  KLog.put(KLOG_DEB, "Setting up asset manager.");
  const char* placeholderTextureLocation = "kiln/assets/img/placeholder-texture.jpg";

  int imgFlags = config.imgfmt;

  if ((IMG_Init(imgFlags) & imgFlags) != imgFlags) {
    KLog.put(KLOG_ERR, "Failed to init SDL_image: %s", IMG_GetError());
    return false;
  }

  if (TTF_Init() == -1) {
    KLog.put(KLOG_ERR, "Failed to init SDL_ttf: %s", TTF_GetError());
    return false;
  }

  if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
    KLog.put(KLOG_ERR, "Failed to init SDL_mixer: %s", Mix_GetError());
    return false;
  }

  Texture::placeholder = this->loadTexture(placeholderTextureLocation, renderer);

  if (!Texture::placeholder) {
    KLog.put(KLOG_ERR, "The placeholder texture could not be loaded. A placeholder is required. Ensure one is supplied at \"%s\".", placeholderTextureLocation);
    return false;
  }

  KLog.put(KLOG_DEB, "Asset Manager initialized!");

  return true;
}

/* Texture */
Texture* AssetManager::loadTexture(std::string path, std::string name, SDL_Renderer* renderer) {
  Texture* texture = new Texture();
  bool success = texture->create(path, renderer);
  
  if (success) {
    KLog.put(KLOG_INF, "Loaded texture %s from %s.", name.c_str(), path.c_str());
    this->TextureMap[name] = texture;
    return texture;
  }
  
  KLog.put(KLOG_ERR, "Failed to create texture! %s", SDL_GetError());
  
  if (Texture::placeholder) {
    this->TextureMap[name] = Texture::placeholder;
    return Texture::placeholder;
  } else {
    return nullptr;
  }
}

Texture* AssetManager::loadTexture(std::string path, SDL_Renderer* renderer) {
  Texture* texture = new Texture();
  bool success = texture->create(path, renderer);

  if (success) {
    KLog.put(KLOG_INF, "Loaded an unmanaged texture from %s.", path.c_str());
    return texture;
  }
  
  KLog.put(KLOG_ERR, "Failed to create texture from %s! %s", path.c_str(), SDL_GetError());
  
  if (Texture::placeholder) {
    return Texture::placeholder;
  } else {
    return nullptr;
  }
}

Texture* AssetManager::fetchTexture(std::string name) {
  auto itr = this->TextureMap.find(name);

  if (itr == this->TextureMap.end()) {
    KLog.put(KLOG_INF, "Failed to fetch texture: %s", name.c_str());
    return Texture::placeholder;
  } else {
    return this->TextureMap[name];
  }
}

void AssetManager::unloadTexture(std::string name) {
  delete this->TextureMap[name];
  this->TextureMap.erase(name);
}

/* Font */
TTF_Font* AssetManager::loadFont(std::string path, int size, std::string name) {
  TTF_Font* font = TTF_OpenFont(path.c_str(), size);

  if (font == NULL) {
    KLog.put(KLOG_ERR, "Failed to load font %s from %s. %s", name.c_str(), path.c_str(), TTF_GetError());
    return nullptr;
  }

  KLog.put(KLOG_INF, "Loaded font %s from %s.", name.c_str(), path.c_str());
  this->FontMap[name] = font;

  return font;
}

TTF_Font* AssetManager::loadFont(std::string path, int size) {
  TTF_Font* font = TTF_OpenFont(path.c_str(), size);

  if (font == NULL) {
    KLog.put(KLOG_ERR, "Failed to load font from %s. %s", path.c_str(), TTF_GetError());
    return nullptr;
  }

  KLog.put(KLOG_INF, "Loaded an unmanaged font from %s.", path.c_str());

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
    KLog.put(KLOG_ERR, "Failed to load music from %s", path.c_str(), Mix_GetError());
    return nullptr;
  }

  KLog.put(KLOG_INF, "Loaded music %s from %s", name.c_str(), path.c_str());
  this->MusicMap[name] = music;
  return music;
}

Mix_Music* AssetManager::loadMusic(std::string path) {
  Mix_Music* music = Mix_LoadMUS(path.c_str());

  if (!music) {
    KLog.put(KLOG_ERR, "Failed to load unamanged music: %s", Mix_GetError());
    return nullptr;
  }

  KLog.put(KLOG_INF, "Loaded unmanaged music from %s.", path.c_str());
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
    KLog.put(KLOG_ERR, "Failed to load sound: %s", Mix_GetError());
    return nullptr;
  }

  KLog.put(KLOG_INF, "Loaded sound %s from %s.", name.c_str(), path.c_str());
  this->SoundMap[name] = sound;
  return sound;
}

Mix_Chunk* AssetManager::loadSound(std::string path) {
  Mix_Chunk* sound = Mix_LoadWAV(path.c_str());

  if (!sound) {
    KLog.put(KLOG_ERR, "Failed to load sound: %s", Mix_GetError());
    return nullptr;
  }

  KLog.put(KLOG_INF, "Loaded unmanaged sound from %s.", path.c_str());
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