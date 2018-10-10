#include "KilnModule.h"
#include "ModuleSub.h"
#include "kiln/engine/Kiln.h"

KilnModule::KilnModule() {}

KilnModule::~KilnModule() {
  for (std::pair<std::string, Sprite*> sprite : this->spriteMap) {
    delete sprite.second;
  }
}

bool KilnModule::init() {
  return true;
}

void KilnModule::start() {}

void KilnModule::handleEvent(SDL_Event* event) {
  this->subState.getActiveState()->handleEvent(event);
}

void KilnModule::tick(float deltaTime) {
  if (this->unwindStack) {
    this->unloadSub();
  }

  this->subState.getActiveState()->tick(deltaTime);
}

void KilnModule::render() {
  if (this->unwindStack) {return;}

  SDL_Renderer* renderer = this->engine->getManagement()->windowManager.getRenderer();
  this->subState.getActiveState()->render(renderer);
}

void KilnModule::updateSubState() {
  this->subState.update(); 
}

bool KilnModule::hasSub() {
  return !this->subState.empty();
}

void KilnModule::bind(Kiln* engine) { 
  this->engine = engine; 
}

Sprite* KilnModule::createSprite(std::string textureName) {
  AssetManager* assets = &this->engine->getManagement()->assetManager;
  Texture* texture = assets->fetchTexture(textureName);
  Sprite* newSprite = new Sprite(texture);
  this->spriteMap[textureName] = newSprite;
  return newSprite;
}

Sprite* KilnModule::fetchSprite(std::string name) {
  return this->spriteMap[name];
}

Texture* KilnModule::fetchTexture(std::string name) {
  return this->engine->getManagement()->assetManager.fetchTexture(name);
}

TTF_Font* KilnModule::fetchFont(std::string name) {
  return this->engine->getManagement()->assetManager.fetchFont(name);
}

void KilnModule::playSound(std::string soundName, int loops) {
  Mix_Chunk* sound = this->engine->getManagement()->assetManager.fetchSound(soundName);
  Mix_PlayChannel(-1, sound, loops);
}

SDL_Renderer* KilnModule::getRenderer() {
  return this->engine->getManagement()->windowManager.getRenderer();
}

void KilnModule::loadSub(ModuleSub* sub) {
  this->loadSubAssets(sub);

  if (this->subState.empty()) {
    this->subState.pushForce(std::unique_ptr<State>(sub));
  } else {
    this->subState.pushState(std::unique_ptr<State>(sub));
  }
}

void KilnModule::unloadSub() {
  this->subState.popState();
}

void KilnModule::quit() {
  this->unwindStack = true;
}

void KilnModule::replaceCurrentSub(ModuleSub* sub) {
  this->subState.replaceState(std::unique_ptr<State>(sub));
}

void KilnModule::loadSubAssets(ModuleSub* sub) {
  AssetManager* assets = &this->engine->getManagement()->assetManager;
  SDL_Renderer* renderer = this->engine->getManagement()->windowManager.getRenderer();

  for (auto asset : sub->getRequiredAssets().textures) {
    assets->loadTexture(asset.first, asset.second, renderer);
  }

  for (auto asset : sub->getRequiredAssets().fonts) {
    assets->loadFont(asset.first, asset.second);
  }

  for (auto asset : sub->getRequiredAssets().sounds) {
    assets->loadSound(asset.first, asset.second);
  }

  for (auto asset : sub->getRequiredAssets().music) {
    assets->loadMusic(asset.first, asset.second);
  }
}

void KilnModule::unloadSubAssets(ModuleSub* sub) {

}