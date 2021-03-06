#include "KilnModule.h"
#include "SubModule.h"
#include "kiln/engine/Kiln.h"
#include "kiln/engine/States/headers/StateMachine.h"
#include "kiln/engine/Core/headers/EventManager.h"
#include "lib/kilnlog/include/KilnLog.h"
#include "kiln/engine/Classes/Entity/headers/Entity.h"

KilnModule::KilnModule() {
  this->subState = new StateMachine();
  this->eventManager = new EventManager();
}

KilnModule::~KilnModule() {
  delete this->subState;
}

bool KilnModule::init() {
  return true;
  KLog.put(KLOG_DEB, "Initializing module.");
}

void KilnModule::start() {
  KLog.put(KLOG_INF, "Kiln Module is starting.");
  SubModule* sub = dynamic_cast<SubModule*>(this->subState->getActiveState().get());

  if (sub) {
    sub->start();
  }
}

void KilnModule::handleEvent(const SDL_Event* event) {
  this->eventManager->addEvent(event);
  // this->subState->getActiveState()->handleEvent(event);
}

void KilnModule::tick(float deltaTime) {
  if (this->unwindStack) {
    this->unloadSub();
  }

  this->eventManager->handleEvents();
  this->subState->getActiveState()->tick(deltaTime);
}

void KilnModule::render(SDL_Renderer* renderer) {
  if (this->unwindStack) {return;}

  this->subState->getActiveState()->render(renderer);
}

void KilnModule::updateSubState() {
  this->subState->update(); 
}

bool KilnModule::hasSub() {
  return !this->subState->empty();
}

void KilnModule::bind(Kiln* engine) {
  KLog.put(KLOG_DEB, "Binding Kiln to module.");
  this->engine = engine; 
}

void KilnModule::bindEntity(Entity* entity) {

}

void KilnModule::bindEventComponent(EventComponent* component) {
  this->eventManager->registerComponent(component);
}

void KilnModule::bindInput(Uint8 keyCode, void(*action)(void)) {
  this->engine->getManagement()->inputManager.bind(keyCode, action);
}

Texture* KilnModule::fetchTexture(const char* name) {
  return this->engine->getManagement()->assetManager.fetchTexture(name);
}

TTF_Font* KilnModule::fetchFont(const char* name) {
  return this->engine->getManagement()->assetManager.fetchFont(name);
}

void KilnModule::playSound(const char* soundName, int loops) {
  Mix_Chunk* sound = this->engine->getManagement()->assetManager.fetchSound(soundName);
  Mix_PlayChannel(-1, sound, loops);
}

SDL_Renderer* KilnModule::getRenderer() {
  return this->engine->getManagement()->windowManager.getRenderer();
}

void KilnModule::loadSub(SubModule* sub) {
  KLog.put(KLOG_DEB, "Loading a new submodule from Kiln Module.");

  this->loadSubAssets(*sub);

  if (this->subState->empty()) {
    this->subState->pushForce(std::unique_ptr<State>(sub));
  } else {
    this->subState->pushState(std::unique_ptr<State>(sub));
  }
}

void KilnModule::unloadSub() {
  // SubModule* sub = dynamic_cast<SubModule*>(this->subState->getActiveState().get());

  // if (sub) {
  //   this->unloadSubAssets(sub);
  // }

  this->subState->popState();
}

void KilnModule::quit() {
  this->unwindStack = true;
}

void KilnModule::replaceCurrentSub(SubModule* sub) {
  this->subState->replaceState(std::unique_ptr<State>(sub));
}

void KilnModule::loadSubAssets(SubModule& sub) {
  KLog.put(KLOG_DEB, "Loading assets for submodule.");
  AssetManager* assets = &this->engine->getManagement()->assetManager;

  for (auto texture : sub.getRequiredAssets().textures) {
    KLog.put(KLOG_DEB, "SUB DEP TEXTURE: %s : %s", texture.first, texture.second);
    assets->loadTexture(texture.first, texture.second);
  }

  for (auto font : sub.getRequiredAssets().fonts) {
    KLog.put(KLOG_DEB, "SUB DEP FONT: %s : %s", font.first.first, font.first.second);
    assets->loadFont(font.first.first, font.second, font.first.second);
  }

  for (auto sound : sub.getRequiredAssets().sounds) {
    KLog.put(KLOG_DEB, "SUB DEP SOUND: %s : %s", sound.first, sound.second);
    assets->loadSound(sound.first, sound.second);
  }

  for (auto music : sub.getRequiredAssets().music) {
    KLog.put(KLOG_DEB, "SUB DEP MUSIC: %s : %s", music.first, music.second);
    assets->loadMusic(music.first, music.second);
  }
}


// TODO: This needs to ensure assets that are required by other states
// in the state machine are not unloaded
// void KilnModule::unloadSubAssets(SubModule* sub) {
//   AssetDependencies assets = sub->getRequiredAssets();
// }