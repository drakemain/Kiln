#include "engine/Kiln.h"
#include "test/test.h"

int main() {
  Kiln kiln;
  Test test;
  
  if (kiln.init(test)) {
    kiln.run(test);
  }

  kiln.cleanup();
}