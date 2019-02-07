#include "engine/Kiln.h"
#include "kiln/TetrisModule/TetrisModule.h"

int main() {
  Kiln kiln;
  TetrisModule tetris;
  
  if (kiln.init(tetris)) {
    kiln.run(tetris);
  }

  kiln.cleanup();
}