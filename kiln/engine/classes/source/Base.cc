#include "../headers/Base.h"

SDL_Renderer* Base::renderer = nullptr;

void Base::setBaseRenderer(SDL_Renderer* renderer) {
  this->renderer = renderer;
}

void Base::destroyBaseRenderer() {
  SDL_DestroyRenderer(Base::renderer);
}

SDL_Renderer* Base::getBaseRenderer() const {
  return this->renderer;
}