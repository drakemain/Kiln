#include "headers/Kiln.h"

int main() {
  Kiln kiln;
  
  if (kiln.init()) {
    kiln.run();
  }

  kiln.cleanup();
}