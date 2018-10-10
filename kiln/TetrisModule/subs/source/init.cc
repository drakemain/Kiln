#include "../headers/init.h"
#include "kiln/engine/Classes/Menu/headers/Button.h"
#include "kiln/engine/Definitions/Colors.h"

InitSub::InitSub(class KilnModule* mod) : ModuleSub(mod) {
  std::cout << "Loaded init sub" << std::endl;

  this->assetDependencies.textures = {
    {"kiln/assets/img/button-bg.png", "btn"}
  };

  this->assetDependencies.sounds = {
    {"kiln/assets/audio/sounds/win98.wav", "win98"}
  };
}

void InitSub::init() {
  this->module->playSound("win98", 0);
  TTF_Font* buttonFont = this->module->fetchFont("StatsFont");
  Texture* buttonTexture = this->module->fetchTexture("btn");
  SDL_Renderer* renderer = this->module->getRenderer();

  this->button = new Button(buttonTexture, "Button", buttonFont, KILN_COLOR::ORANGE, renderer);
  
  std::cout << "Setting Button Position" << std::endl;
  this->button->setWorldPosition(50.f, 50.f);
  this->button->setScale(.5);

  this->button->bindAction([this](){this->module->unloadSub();});
}

void InitSub::cleanup() {}
void InitSub::pause() {}
void InitSub::resume() {}
void InitSub::handleEvent(SDL_Event* event) {
  if (event->type == SDL_MOUSEBUTTONDOWN) {
    if (event->button.clicks == SDL_BUTTON_LEFT) {
      ICoordinate coord;
      SDL_GetMouseState(&coord.x, &coord.y);
      this->button->ifClicked(coord);
      this->button->setWorldPosition((float)coord.x, (float)coord.y);
    }
  }
}

void InitSub::tick(float deltaTime) {
  this->runtime += deltaTime;

  // if (this->runtime > 3000) {
  //   this->module->unloadSub();
  // }
}
void InitSub::render(SDL_Renderer* renderer) {
  // this->module->fetchSprite("btn")->render(renderer);
  this->button->render(renderer);
}