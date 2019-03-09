#include "../headers/WindowManager.h"
#include "../headers/ConfigLoader/WindowConfig.h"
#include "lib/kilnlog/include/KilnLog.h"
#include <SDL.h>

bool WindowManager::init(const WindowConfig& conf) {
  KLog.put(KLOG_DEB, "Setting up window manager.");

  this->title = conf.title;
  this->WIDTH = conf.w;
  this->HEIGHT = conf.h;

  this->window = SDL_CreateWindow(this->title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, this->WIDTH, this->HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);

  if (this->window == NULL) {
    KLog.put(KLOG_ERR, "Failed to initialize window! %s", SDL_GetError());
    return false;
  }

  this->renderer = SDL_CreateRenderer(this->window, -1, conf.renderFlags);

  if (this->renderer == NULL) {
    KLog.put(KLOG_ERR, "Failed to initialize renderer! %s", SDL_GetError());
    return false;
  }
  
  this->setFrameLimit(this->FRAME_LIMIT_PER_SECOND);

  KLog.put(KLOG_DEB, "Window manager initialized.");

  return true;
}

void WindowManager::cleanup() {
  KLog.put(KLOG_DEB, "Cleaning up window manager.");
  SDL_DestroyRenderer(this->renderer);
  SDL_DestroyWindow(this->window);
}

SDL_Window* WindowManager::getWindow() const {
  return this->window;
}

SDL_Renderer* WindowManager::getRenderer() const {
  return this->renderer;
}

Dim WindowManager::getResolution() const {
  return {this->WIDTH, this->HEIGHT};
}

void WindowManager::setResolution(const Dim newRes) {
  this->WIDTH = newRes.w;
  this->HEIGHT = newRes.h;

  if (this->window) {
    SDL_SetWindowSize(this->window, this->WIDTH, this->HEIGHT);
  } else {
    KLog.put(KLOG_WAR, "Attempted to set resolution while there is no window!");
  }
}

float WindowManager::getFrameLimit() const {
  return this->FRAME_LIMIT_PER_SECOND;
}

float WindowManager::getMinFrameTimePerSecond() const {
  return this->MIN_FRAME_TIME_S;
}

float WindowManager::getMinFrameTimePerMilli() const {
  return this->MIN_FRAME_TIME_MS;
}

void WindowManager::setFrameLimit(float frameLimit) {
  this->FRAME_LIMIT_PER_SECOND = frameLimit;
  this->MIN_FRAME_TIME_S = 1.f / frameLimit;
  this->MIN_FRAME_TIME_MS = 1000.f / frameLimit;
}