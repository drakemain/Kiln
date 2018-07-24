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
  this->movableSprite = new MovableSprite(testTexture);
  this->testText = new Text("Init State Text!", testFont, KILN_COLOR::MEDIUM_GREY, renderer);
  this->testText->setWorldPosition(0, this->testText->getDimensions().h);
  this->sound = testSound;

  this->movableSprite->setWidth(100);
  this->movableSprite->setHeight(100);
  this->movableSprite->setWorldPosition(640 - 100, 0);
  this->movableSprite->setVelocity(-77.f, 10.f);
  
  std::cout << "INIT STATE INIT COMPLETE" << std::endl;

  Mix_PlayChannel(-1, this->sound, 0);
}

void InitState::cleanup() {
  std::cout << "Cleanup INIT" << std::endl;

  delete this->testSprite;
  delete this->movableSprite;
  delete this->testText;

  this->coreManagement.assetManager.unloadSound("Win98");
  this->coreManagement.assetManager.unloadTexture("SpriteTest");
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

  // movetest
  FCoordinate oldPos = this->movableSprite->getWorldPosition();

  this->movableSprite->tick(deltaTime);

  this->movableSprite->setRotation(this->movableSprite->getRotationDegrees() + (0.051f * deltaTime * 2));

  FCoordinate newPos = this->movableSprite->getWorldPosition();
  vxSum += std::abs(oldPos.x - newPos.x) / (deltaTime/1000.f);
  vySum += std::abs(oldPos.y - newPos.y) / (deltaTime/1000.f);
  ++vSamples;

  if (vSamples >= 10) {
    vx = vxSum / vSamples;
    vy = vySum / vSamples;
    vSamples = 0;
    vxSum = 0;
    vySum = 0;
    testText->setText("Vx: " + std::to_string(vx) + " Vy: " + std::to_string(vy) + " V: " + std::to_string(this->movableSprite->getVelocity().magnitude()));
    testText->draw(this->coreManagement.windowManager.getRenderer());
  }
  //

  this->render();
}

void InitState::render() {
  SDL_Renderer* renderer = this->coreManagement.windowManager.getRenderer();
  this->testSprite->render(renderer);
  this->movableSprite->render(renderer);
  this->testText->render(renderer);
}