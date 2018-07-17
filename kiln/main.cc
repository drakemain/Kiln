#include "engine/Kiln.h"

int main() {
  Kiln kiln;
  
  if (kiln.init()) {
    kiln.loadAssets();
    kiln.run();
  }

  kiln.cleanup();
}