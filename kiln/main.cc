#include "headers/Kiln.h"

int main() {
  Kiln kiln;

  kiln.init();
  kiln.run();
  kiln.cleanup();
}