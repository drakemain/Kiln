#include "headers/Kiln.h"

int main() {
  Kiln kiln;

  kiln.init();
  kiln.run();

  SDL_Delay(3000);
  kiln.cleanup();
}