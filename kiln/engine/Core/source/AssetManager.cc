#include "../headers/AssetManager.h"
#include "../headers/ConfigLoader/AssetConfig.h"
#include "kiln/engine/Core/headers/Texture.h"
#include "lib/kilnlog/include/KilnLog.h"

AssetManager::AssetManager() {}

AssetManager::~AssetManager() {
  KLog.put(KLOG_DEB, "Cleaning up managed assets.");

  for (auto textureItr = this->TextureMap.begin(); textureItr != this->TextureMap.end(); ++textureItr) {
    delete textureItr->second;
  }

  for (auto fontItr = this->FontMap.begin(); fontItr != this->FontMap.end(); ++fontItr) {
    TTF_CloseFont(fontItr->second);
    KLog.put(KLOG_INF, "Cleanup FONT: %s", fontItr->first);
  }

  for (auto musicItr = this->MusicMap.begin(); musicItr != this->MusicMap.end(); ++musicItr) {
    Mix_FreeMusic(musicItr->second);
    KLog.put(KLOG_INF, "Cleanup MUSIC: %s", musicItr->first);
  }

  for (auto soundIter = this->SoundMap.begin(); soundIter != this->SoundMap.end(); ++soundIter) {
    Mix_FreeChunk(soundIter->second);
    KLog.put(KLOG_INF, "Cleanup SOUND: %s", soundIter->first);
  }

  delete this->placeholderTexture;

  IMG_Quit();
  TTF_Quit();
  Mix_Quit();
}

bool AssetManager::init(SDL_Renderer* renderer, const AssetConfig& config) {
  KLog.put(KLOG_DEB, "Setting up asset manager.");

  if (!renderer) {
    KLog.put(KLOG_ERR, "A renderer was not supplied to the asset manager.");
    return false;
  }

  this->renderer = renderer;

  int imgFlags = config.imgfmt;

  if ((IMG_Init(imgFlags) & imgFlags) != imgFlags) {
    KLog.put(KLOG_ERR, "Failed to init SDL_image: \"%s\"", IMG_GetError());
    return false;
  }

  if (TTF_Init() == -1) {
    KLog.put(KLOG_ERR, "Failed to init SDL_ttf: \"%s\"", TTF_GetError());
    return false;
  }

  if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
    KLog.put(KLOG_ERR, "Failed to init SDL_mixer: \"%s\"", Mix_GetError());
    return false;
  }

  if (!this->loadPlaceholders()) {
    KLog.put(KLOG_ERR, "One or more placeholder assets failed to load.");
    return false;
  }

  KLog.put(KLOG_DEB, "Asset Manager initialized!");

  return true;
}

/* Texture */
Texture* AssetManager::loadTexture(const char* path, const char* identifier) {
  Texture* texture = loadTexture(path);

  if (texture) {
    KLog.put(KLOG_INF, "Loaded texture \"%s\" from \"%s\".", identifier, path);
  } else {
    KLog.put(KLOG_WAR, "Failed to load texture \"%s\" from \"%s\"", identifier, path);
    texture = this->placeholderTexture;
  }

  this->TextureMap.insert({identifier, texture});
  return texture;
}

Texture* AssetManager::fetchTexture(const char* identifier) {
  auto itr = this->TextureMap.find(identifier);

  if (itr == this->TextureMap.end()) {
    KLog.put(KLOG_WAR, "Failed to fetch texture: \"%s\".", identifier);
    return this->placeholderTexture;
  } else {
    return itr->second;
  }
}

void AssetManager::unloadTexture(const char* identifier) {
  auto itr = this->TextureMap.find(identifier);

  if (itr == this->TextureMap.end()) {
    KLog.put(KLOG_WAR, "Attempted to unload texture \"%s\", but it wasn't in the texture map.", identifier);
    return;
  }

  KLog.put(KLOG_INF, "Unloaded texture %s.", identifier);

  delete itr->second;
  this->TextureMap.erase(itr);
}

/* Font */
TTF_Font* AssetManager::loadFont(const char* path, int size, const char* identifier) {
  TTF_Font* font = this->loadFont(path, size);

  if (!font) {
    KLog.put(KLOG_WAR, "Failed to load font \"%s\" from \"%s\". \"%s\"", identifier, path, TTF_GetError());
    // TODO: Placeholder font
  } else {
    KLog.put(KLOG_INF, "Loaded font %dpt font \"%s\" from \"%s\"", size, identifier, path);
  }

  this->FontMap.insert({identifier, font});
  return font;
}

TTF_Font* AssetManager::fetchFont(const char* identifier) {
  // TODO: handle key DNE
  auto itr = this->FontMap.find(identifier);

  if (itr == this->FontMap.end()) {
    KLog.put(KLOG_WAR, "Failed to fetch font \"%s\".", identifier);
    // TODO: Return placeholder
    return nullptr;
  }

  return itr->second;
}

void AssetManager::unloadFont(const char* identifier) {
  auto itr = this->FontMap.find(identifier);

  if (itr == this->FontMap.end()) {
    KLog.put(KLOG_WAR,  "Attempted to unload font \"%s\", but it wasn't in the texture map.", identifier);
    return;
  }

  KLog.put(KLOG_INF, "Unloaded font \"%s\"", identifier);
  
  TTF_CloseFont(itr->second);
  this->FontMap.erase(identifier);
}

/* Music */
Mix_Music* AssetManager::loadMusic(const char* path, const char* identifier) {
  Mix_Music* music = this->loadMusic(path);

  if (!music) {
    KLog.put(KLOG_WAR, "Failed to load music \"%s\" from \"%s\". %s", identifier, path, Mix_GetError());
    return nullptr;
  }

  KLog.put(KLOG_INF, "Loaded music \"%s\" from \"%s\"", identifier, path);
  
  this->MusicMap.insert({identifier, music});
  return music;
}

Mix_Music* AssetManager::fetchMusic(const char* identifier) {
  auto itr = this->MusicMap.find(identifier);

  if (itr == this->MusicMap.end()) {
   KLog.put(KLOG_WAR, "Failed to fetch music \"%s\".", identifier);
    // TODO: Return placeholder
    return nullptr;
  }

  return itr->second;
}

void AssetManager::unloadMusic(const char* identifier) {
  auto itr = this->MusicMap.find(identifier);

  if (itr == this->MusicMap.end()) {
    KLog.put(KLOG_WAR, "Attempted to unload music \"%s\", but it wasn't in the texture map.", identifier);
    return;
  }

  KLog.put(KLOG_INF, "Unloaded music %s.", identifier);

  Mix_FreeMusic(itr->second);
  this->MusicMap.erase(itr);
}


/* Sound */
Mix_Chunk* AssetManager::loadSound(const char* path, const char* identifier) {
  Mix_Chunk* sound = this->loadSound(path);

  if (!sound) {
    KLog.put(KLOG_WAR, "Failed to load sound \"%s\" from \"%s\". %s", identifier, path, Mix_GetError());
    return nullptr;
  }

  KLog.put(KLOG_INF, "Loaded sound \"%s\" from \"%s\"", identifier, path);
  
  this->SoundMap.insert({identifier, sound});
  return sound;
}

Mix_Chunk* AssetManager::fetchSound(const char* identifier) {
  auto itr = this->SoundMap.find(identifier);

  if (itr == this->SoundMap.end()) {
   KLog.put(KLOG_WAR, "Failed to fetch sound \"%s\".", identifier);
    // TODO: Return placeholder
    return nullptr;
  }

  return itr->second;
}

void AssetManager::unloadSound(const char* identifier) {
  auto itr = this->SoundMap.find(identifier);

  if (itr == this->SoundMap.end()) {
    KLog.put(KLOG_WAR, "Attempted to unload sound \"%s\", but it wasn't in the texture map.", identifier);
    return;
  }

  KLog.put(KLOG_INF, "Unloaded sound %s.", identifier);

  Mix_FreeChunk(itr->second);
  this->SoundMap.erase(itr);
}

Texture* AssetManager::loadTexture(const char* path) {
  Texture* texture = Texture::newTexture(path, renderer);

  return texture;
}

TTF_Font* AssetManager::loadFont(const char* path, int size) {
  TTF_Font* font = TTF_OpenFont(path, size);
  return font;
}

Mix_Music* AssetManager::loadMusic(const char* path) {
  Mix_Music* music = Mix_LoadMUS(path);
  return music;
}

Mix_Chunk* AssetManager::loadSound(const char* path) {
  Mix_Chunk* chunk = Mix_LoadWAV(path);
  return chunk;
}

bool AssetManager::loadPlaceholders() {
  KLog.put(KLOG_INF, "Loading placeholder assets.");
  this->placeholderTexture = loadTexture("kiln/assets/img/placeholder-texture.jpg");
  // placehoder font
  // placeholder music
  // placeholder sound

  return this->placeholderTexture;
}