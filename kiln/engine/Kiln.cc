#include "Kiln.h"
#include "lib/kilnlog/include/KilnLog.h"
#include "Module/KilnModule.h"
#include "Core/headers/Stats.h"
#include "Core/headers/ConfigLoader/ConfigLoader.h"
#include "Definitions/Colors.h"
#include <SDL.h>

Kiln::Kiln() {}

Kiln::~Kiln() {}

bool Kiln::init(KilnModule& module) {
  ConfigLoader config;
  config.load("kiln/config.toml");

  LogConfig logConfig = config.logs();
  KLog.setSilent(logConfig.silent);
  if (logConfig.flushOnStart) {
    KLog.flush();
  }
  KLog.setLevel(logConfig.level);

  KLog.put(KLOG_DEB, "Initializing Kiln.");

  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    KLog.put(KLOG_ERR, "Failed to initialize SDL! %s", SDL_GetError());
    return false;
  }

  if (!this->coreManagement.windowManager.init(config.window())) {
    KLog.put(KLOG_ERR, "The window manager failed to initialize.");
    return false;
  }

  if (!this->coreManagement.assetManager.init(this->coreManagement.windowManager.getRenderer(), config.asset())) {
    KLog.put(KLOG_ERR, "The asset manager failed to initialize.");
    return false;
  }

  TTF_Font* fpsFont = this->coreManagement.assetManager.loadFont("kiln/assets/font/RobotoMono-Regular.ttf", 32, "StatsFont");
  this->stats = new Stats(10, true, fpsFont, this->coreManagement.windowManager.getRenderer());
  module.bind(this);
  if (!module.init()) {
    KLog.put(KLOG_ERR, "Failed to load module! %s", SDL_GetError());
    return false;
  }

  KLog.put(KLOG_INF, "Successfully initialized Kiln Module.");

  this->getManagement()->inputManager.bindInputComponents();
  return true;
}

void Kiln::run(KilnModule& module) {
  // time at the start of a frame in ms
  Uint32 tickStartTime;
  // time at the start of the previous frame in ms
  Uint32 lastTickStartTime = 0;
  // amount of time passed since previous frame in seconds
  float deltaTime = 0.f;

  module.start();

  KLog.put(KLOG_DEB, "Entering core loop.");
  while(isRunning && module.hasSub()) {
    tickStartTime = SDL_GetTicks();
    deltaTime = (float)(tickStartTime - lastTickStartTime) / 1000.f;

    if (this->quit) {
      module.quit();
    }
    
    while(this->coreManagement.inputManager.poll()) {
      const SDL_Event* polledEvent = this->coreManagement.inputManager.getLastEvent();
      this->checkEngineEvent(polledEvent);
    }

    this->coreManagement.inputManager.handleInputs();

    module.tick(deltaTime);
    this->stats->tick(deltaTime);

    SDL_Renderer* renderer = this->coreManagement.windowManager.getRenderer();
    SDL_RenderClear(renderer);

    this->render(module);

    module.updateSubState();

    // Abide by frame limit
    // SDL_GetTicks() isn't accurate enough for this. A better solution is needed.
    float tickTime = SDL_GetTicks() - tickStartTime;
    Uint32 minFrameTime = (Uint32)(this->coreManagement.windowManager.getMinFrameTimePerMilli());
    if (tickTime < minFrameTime) {
      SDL_Delay(minFrameTime - tickTime);
    }

    this->stats->incrementFrameCount();
    lastTickStartTime = tickStartTime;
  }
}

void Kiln::cleanup() {
  if (this->quit) {
    KLog.put(KLOG_DEB, "All submodules were popped.");
  }

  KLog.put(KLOG_DEB, "Cleaning up core.");

  if (this->stats) {
    delete this->stats;
  }

  this->coreManagement.windowManager.cleanup();

  SDL_Quit();
}

/* Helper Functions */
void Kiln::checkEngineEvent(const SDL_Event* event) {
  if (event) {
    if (event->type == SDL_QUIT) {
      this->quit = true;
    }
  }
}

void Kiln::render(KilnModule& module) {
  SDL_Renderer* renderer = this->getManagement()->windowManager.getRenderer();
  module.render(renderer);
  this->stats->render(renderer);
  
  SDL_RenderPresent(renderer);
}
