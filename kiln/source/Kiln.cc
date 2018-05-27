#include "kiln/headers/Kiln.h"
#include <iostream>

bool Kiln::init() {
  std::cout << "This is the Kiln init method." << std::endl;

  return true;
}

void Kiln::run() {
  std::cout << "This is the Kiln run method." << std::endl;
}

void Kiln::cleanup() {
  std::cout << "This is the Kiln cleanup method." << std::endl;
}