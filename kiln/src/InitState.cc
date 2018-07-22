#include "InitState.h"
#include "kiln/engine/Definitions/Colors.h"
#include "kiln/engine/Classes/Menu/headers/Menu.h"
#include <iostream>

InitState::InitState(CoreManagement& coreManagement)
: coreManagement(coreManagement) {}

InitState::~InitState() {
  this->cleanup();
}

void InitState::init() {
  SDL_Renderer* renderer = this->coreManagement.windowManager.getRenderer();
  Texture* testTexture = this->coreManagement.assetManager.loadTexture("kiln/assets/img/sprite-test.jpg", "SpriteTest", renderer);
  TTF_Font* testFont = this->coreManagement.assetManager.loadFont("kiln/assets/font/RobotoMono-Regular.ttf", "Roboto");
  Mix_Chunk* testSound = this->coreManagement.assetManager.loadSound("kiln/assets/audio/sounds/win98.wav", "Win98");

  std::cout << "INIT STATE INIT" << std::endl;

  this->testSprite = new Sprite(testTexture);
  this->testText = new Text("Init State Text!", testFont, KILN_COLOR::MEDIUM_GREY, renderer);
  this->testText->setWorldPosition(0, this->testText->getDimensions().h);
  this->sound = testSound;
  
  std::cout << "INIT STATE INIT COMPLETE" << std::endl;

  Mix_PlayChannel(-1, this->sound, 0);
}

void InitState::cleanup() {
  std::cout << "Cleanup INIT" << std::endl;

  delete this->testSprite;
  delete this->testText;

  this->coreManagement.assetManager.unloadSound("Win98");
}

void InitState::pause() {}

void InitState::resume() {}

void InitState::handleEvent(SDL_Event* event) {
  if (event) {
    std::cout << "INIT EVENT!" << std::endl;
  }
}

void InitState::tick(float deltaTime) {
  this->runTime += deltaTime;

  if (this->runTime > 7000) {
    this->coreManagement.state.replaceState(std::unique_ptr<State>(new Menu(this->coreManagement)));
  }

  this->render();
}

void InitState::render() {
  SDL_Renderer* renderer = this->coreManagement.windowManager.getRenderer();
  this->testSprite->render(renderer);
  this->testText->render(renderer);
}