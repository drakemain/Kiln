#include "KilnModule.h"
#include "ModuleSub.h"
#include "kiln/engine/Kiln.h"
#include "kiln/engine/States/headers/StateMachine.h"
#include "kiln/engine/Core/headers/LayerManager.h"

KilnModule::KilnModule() {
  this->layerManager = new LayerManager();
  this->subState = new StateMachine();
}

KilnModule::~KilnModule() {
  delete this->layerManager;
  delete this->subState;
}

bool KilnModule::init() {
  return true;
}

void KilnModule::start() {}

void KilnModule::handleEvent(SDL_Event* event) {
  this->subState->getActiveState()->handleEvent(event);
}

void KilnModule::tick(float deltaTime) {
  if (this->unwindStack) {
    this->unloadSub();
  }

  this->subState->getActiveState()->tick(deltaTime);
  this->layerManager->update();
}

void KilnModule::render() {
  if (this->unwindStack) {return;}

  SDL_Renderer* renderer = this->engine->getManagement()->windowManager.getRenderer();
  this->subState->getActiveState()->render(renderer);
}

void KilnModule::updateSubState() {
  this->subState->update(); 
}

bool KilnModule::hasSub() {
  return !this->subState->empty();
}

void KilnModule::bind(Kiln* engine) { 
  this->engine = engine; 
}

void KilnModule::bindEntity(Entity* entity) {

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
  this->loadSubAssets(*sub);

  if (this->subState->empty()) {
    this->subState->pushForce(std::unique_ptr<State>(sub));
  } else {
    this->subState->pushState(std::unique_ptr<State>(sub));
  }
}

void KilnModule::unloadSub() {
  this->subState->popState();
}

void KilnModule::quit() {
  this->unwindStack = true;
}

void KilnModule::replaceCurrentSub(ModuleSub* sub) {
  this->subState->replaceState(std::unique_ptr<State>(sub));
}

void KilnModule::unloadSubAssets(ModuleSub* sub) {

}


void KilnModule::loadSubAssets(ModuleSub& sub) {
  AssetManager* assets = &this->engine->getManagement()->assetManager;
  SDL_Renderer* renderer = this->engine->getManagement()->windowManager.getRenderer();

  for (auto texture : sub.getRequiredAssets().textures) {
    assets->loadTexture(texture.first, texture.second, renderer);
  }

  for (auto font : sub.getRequiredAssets().fonts) {
    assets->loadFont(font.first.first, font.second, font.first.second);
  }

  for (auto sound : sub.getRequiredAssets().sounds) {
    assets->loadSound(sound.first, sound.second);
  }

  for (auto music : sub.getRequiredAssets().music) {
    assets->loadMusic(music.first, music.second);
  }
}