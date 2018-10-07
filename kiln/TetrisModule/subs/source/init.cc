#include "../headers/init.h"

InitSub::InitSub(class KilnModule* mod) :ModuleSub(mod) {
  this->assetDependencies.textures = {
    {"kiln/assets/img/button-bg.png", "btn"}
  };
  this->assetDependencies.sounds = {
    {"kiln/assets/audio/sounds/win98.wav", "win98"}
  };
  
}
void InitSub::init() {
  this->module->createSprite("btn");
  std::cout << "Created sprite." << std::endl;
  // Mix_PlayChannel(-1, this->module->assets->fetchSound("win98"), 0);
}

void InitSub::cleanup() {}
void InitSub::pause() {}
void InitSub::resume() {}
void InitSub::handleEvent(SDL_Event* event) {}
void InitSub::tick(float deltaTime) {
  this->runtime += deltaTime;

  if (this->runtime > 3000) {
    this->module->unloadSub();
  }
}
void InitSub::render(SDL_Renderer* renderer) {
  this->module->fetchSprite("btn")->render(renderer);
}