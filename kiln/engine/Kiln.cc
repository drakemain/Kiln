#include "Kiln.h"
#include "Definitions/Colors.h"
#include <iostream>

Kiln::Kiln() {}

bool Kiln::init(KilnModule& module) {
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

  TTF_Font* fpsFont = this->coreManagement.assetManager.loadFont("kiln/assets/font/RobotoMono-Regular.ttf", "StatsFont");
  this->stats = new Stats(10, true, fpsFont, this->coreManagement.windowManager.getRenderer());

  module.bind(&this->coreManagement.assetManager);
  module.bind(&this->coreManagement.windowManager);

  if (!module.init()) {
    return false;
  }

  return true;
}

void Kiln::run(KilnModule& module) {
  std::cout << "RUN" << std::endl;

  const unsigned int frameLimit = 60;
  const float minFrameTime = 1000.f / frameLimit;
  unsigned int frameTime = 0;
  Uint32 tickStartTime;
  Uint32 lastTickStartTime = 0;
  
  float deltaTime = 0;

  module.start();

  while(isRunning) {
    tickStartTime = SDL_GetTicks();
    deltaTime = tickStartTime - lastTickStartTime;
    
    while(this->coreManagement.inputManager.poll()) {
      SDL_Event* polledEvent = this->coreManagement.inputManager.getEvent();
      this->checkEngineEvent(polledEvent);
      module.handleEvent(polledEvent);
    }

    module.tick(deltaTime);

    SDL_Renderer* renderer = this->coreManagement.windowManager.getRenderer();
    SDL_RenderClear(renderer);

    module.render();
    this->stats->getText()->render(renderer);
    
    SDL_RenderPresent(renderer);

    // this->render();

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
void Kiln::checkEngineEvent(SDL_Event* event) {
  if (event) {
    if (event->type == SDL_QUIT) {
      std::cout << "QUIT EVENT" << std::endl;
      this->isRunning = false;
    }
  }
}

void Kiln::render() {
  SDL_Renderer* renderer = this->coreManagement.windowManager.getRenderer();
  SDL_RenderClear(renderer);

  this->stats->getText()->render(renderer);
  
  SDL_RenderPresent(renderer);
}