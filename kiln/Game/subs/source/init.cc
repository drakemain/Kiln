#include "../headers/init.h"
#include "kiln/engine/Classes/Menu/headers/Button.h"
#include "kiln/engine/Classes/Components/headers/TextComponent.h"
#include "kiln/engine/Definitions/Colors.h"
#include "kiln/Game/subs/headers/mainmenu.h"
#include "kiln/engine/Classes/Entity/headers/Sprite.h"
#include "kiln/engine/Core/headers/LayerManager.h"
#include "kiln/Game/classes/InputCompTest.h"

InitSub::InitSub(class KilnModule* mod) : SubModule(mod) {
  std::cout << "Loaded init sub" << std::endl;

  this->assetDependencies.textures = {
    {"kiln/assets/img/button-bg.png", "btn"},
    {"kiln/assets/img/sprite-test.jpg", "spr"}
  };

  this->assetDependencies.fonts = {
    {{"kiln/assets/font/RobotoMono-Regular.ttf", "btn"}, 128}
  };

  this->assetDependencies.sounds = {
    {"kiln/assets/audio/sounds/win98.wav", "win98"}
  };
}

void test();

void InitSub::init() {
  this->module->playSound("win98", 0);
  TTF_Font* buttonFont = this->module->fetchFont("btn");
  Texture* buttonTexture = this->module->fetchTexture("btn");
  SDL_Renderer* renderer = this->module->getRenderer();

  Button* button = new Button(buttonTexture, "Button", buttonFont, KILN_COLOR::ORANGE, renderer);
  Sprite* sprite = new Sprite(this->module->fetchTexture("btn"));
  Sprite* sprite2 = new Sprite(this->module->fetchTexture("spr"));
  Sprite* sprite3 = new Sprite(this->module->fetchTexture("dne"));

  InputCompTest* test = new InputCompTest(this->module->fetchTexture("btn"), buttonFont, renderer);
  
  this->registerEntity(button);
  this->registerEntity(sprite);
  this->registerEntity(sprite2);
  this->registerEntity(sprite3);
  this->registerEntity(test);

  this->getLayerManager()->moveToNewTop(sprite);
  this->getLayerManager()->moveToNewTop(button);
  this->getLayerManager()->moveToTop(test);
  sprite->setWorldPosition({25, 25});
  sprite2->setWorldPosition({100, 100});
  sprite3->scale(.2);
  button->setWorldPosition(0.f, 150.f);
  button->scale(.5);
  button->bindAction([this](){this->module->quit();});
}

void InitSub::cleanup() {}
void InitSub::pause() {}
void InitSub::resume() {}
void InitSub::handleEvent(SDL_Event* event) {
  if (event->type == SDL_MOUSEBUTTONDOWN) {
    if (event->button.clicks == SDL_BUTTON_LEFT) {
      ICoordinate coord;
      SDL_GetMouseState(&coord.x, &coord.y);
      // this->button->checkWasClicked(coord);
      // this->button->setWorldPosition((float)coord.x, (float)coord.y);
    }
  }
}

void InitSub::tick(float deltaTime) {
  SubModule::tick(deltaTime);
  this->runtime += deltaTime;
  // if (this->runtime > 3000) {
  //   this->module->unloadSub();
  // }
}

void InitSub::render(SDL_Renderer* renderer) {
  SubModule::render(renderer);
  // this->testSprite->render(renderer);
}