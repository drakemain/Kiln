#include "Kiln.h"
#include "Module/KilnModule.h"
#include "Core/headers/Stats.h"
#include "Core/headers/ConfigLoader/ConfigLoader.h"
#include "Definitions/Colors.h"
#include <iostream>
#include <SDL.h>

Kiln::Kiln() {}

Kiln::~Kiln() {}

bool Kiln::init(KilnModule& module) {
  std::cout << "Initializing kiln." << std::endl;

  ConfigLoader config;
  std::cout << "\tFetching config." << std::endl;
  config.load("kiln/config.toml");

  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    std::cerr << "Failed to init SDL:\n\t|_> " << SDL_GetError() << std::endl;
    return false;
  }

  if (!this->coreManagement.windowManager.init(config.window())) {
    return false;
  }

  if (!this->coreManagement.assetManager.init(this->coreManagement.windowManager.getRenderer(), config.asset())) {
    return false;
  }

  TTF_Font* fpsFont = this->coreManagement.assetManager.loadFont("kiln/assets/font/RobotoMono-Regular.ttf", 32, "StatsFont");
  this->stats = new Stats(10, true, fpsFont, this->coreManagement.windowManager.getRenderer());
  module.bind(this);
  if (!module.init()) {
    return false;
  }

  this->getManagement()->inputManager.bindInputComponents();
  return true;
}

void Kiln::run(KilnModule& module) {
  std::cout << "RUN" << std::endl;
  
  // time at the start of a frame in ms
  Uint32 tickStartTime;
  // time at the start of the previous frame in ms
  Uint32 lastTickStartTime = 0;
  // amount of time passed since previous frame in seconds
  float deltaTime = 0.f;

  module.start();

  while(isRunning && module.hasSub()) {
    tickStartTime = SDL_GetTicks();
    deltaTime = (float)(tickStartTime - lastTickStartTime) / 1000.f;
    
    while(this->coreManagement.inputManager.poll()) {
      const SDL_Event* polledEvent = this->coreManagement.inputManager.getLastEvent();
      this->checkEngineEvent(polledEvent);
    }

    this->coreManagement.inputManager.handleInputs();

    module.tick(deltaTime);
    this->stats->tick(deltaTime);

    SDL_Renderer* renderer = this->coreManagement.windowManager.getRenderer();
    SDL_RenderClear(renderer);

    module.render();
    this->render(renderer);

    module.updateSubState();

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
void Kiln::checkEngineEvent(const SDL_Event* event) {
  if (event) {
    if (event->type == SDL_QUIT) {
      std::cout << "QUIT EVENT" << std::endl;
      this->isRunning = false;
    }
  }
}

void Kiln::render(SDL_Renderer* renderer) {
  this->stats->render(renderer);
  
  SDL_RenderPresent(renderer);
}