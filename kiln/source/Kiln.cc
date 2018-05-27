#include "kiln/headers/Kiln.h"
#include <iostream>

bool Kiln::init() {
  std::cout << "INIT" << std::endl;
  bool success = true;

  this->window = SDL_CreateWindow("Kiln", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, this->WIDTH, this->HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);

  if (this->window == NULL) {
    success = false;
  }

  return success;
}

void Kiln::run() {
  std::cout << "This is the Kiln run method." << std::endl;
}

void Kiln::cleanup() {
  std::cout << "This is the Kiln cleanup method." << std::endl;

  SDL_DestroyWindow(this->window);
}