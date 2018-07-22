#include "Kiln.h"
#include "kiln/src/InitState.h"
#include "Definitions/Colors.h"
#include <iostream>

Kiln::Kiln() {}

bool Kiln::init() {
  std::cout << "INIT" << std::endl;

  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    std::cerr << "Failed to init SDL:\n\t" << SDL_GetError() << std::endl;
    return false;
  }

  if (!this->coreManagement.windowManager.init()) {
    return false;
  }

  if (!this->coreManagement.assetManager.init(this->coreManagement.windowManager.getRenderer())) {
    return false;
  }

  this->coreManagement.state.pushForce(std::unique_ptr<State>(new InitState(this->coreManagement)));

  TTF_Font* fpsFont = this->coreManagement.assetManager.loadFont("kiln/assets/font/RobotoMono-Regular.ttf", "StatsFont");
  this->stats = new Stats(10, true, fpsFont, this->coreManagement.windowManager.getRenderer());
  
  return true;
}

void Kiln::run() {
  std::cout << "RUN" << std::endl;

  const unsigned int frameLimit = 60;
  const float minFrameTime = 1000.f / frameLimit;
  unsigned int frameTime = 0;
  Uint32 tickStartTime;
  Uint32 lastTickStartTime = 0;
  
  float deltaTime = 0;

  while(isRunning && !this->coreManagement.state.empty()) {
    tickStartTime = SDL_GetTicks();
    deltaTime = tickStartTime - lastTickStartTime;

    this->coreManagement.state.update();
    
    while(this->coreManagement.inputManager.poll()) {
      SDL_Event* polledEvent = this->coreManagement.inputManager.getEvent();
      
      this->checkQuit(polledEvent);
      this->coreManagement.state.getActiveState()->handleEvent(polledEvent);
    }    

    this->tick(deltaTime);

    this->render();

    frameTime = SDL_GetTicks() - tickStartTime;
    
    if (frameTime < minFrameTime) {
      // TODO: Don't use delay to limit fps
      SDL_Delay(minFrameTime - frameTime);
      frameTime = SDL_GetTicks() - tickStartTime;
    }

    this->stats->incrementFrameCount();

    lastTickStartTime = tickStartTime;
  }
}

void Kiln::cleanup() {
  std::cout << "CLEANUP" << std::endl;

  delete this->stats;

  this->coreManagement.windowManager.cleanup();

  SDL_Quit();
}

/* Helper Functions */
void Kiln::checkQuit(SDL_Event* event) {
  if (event) {
    if (event->type == SDL_QUIT) {
      std::cout << "QUIT EVENT" << std::endl;
      this->isRunning = false;
    }
  }
}

void Kiln::tick(float deltaTime) {
  // TODO: check tick rate
  this->coreManagement.state.getActiveState()->tick(deltaTime);
}

void Kiln::render() {
  SDL_Renderer* renderer = this->coreManagement.windowManager.getRenderer();
  SDL_RenderClear(renderer);
  
  this->coreManagement.state.getActiveState()->render();
  this->stats->getText()->render(renderer);
  
  SDL_RenderPresent(renderer);
  
}