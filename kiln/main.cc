#include "engine/Kiln.h"
#include "TetrisModule/TetrisModule.h"

int main() {
  Kiln kiln;
  TetrisModule tetris;
  
  if (kiln.init(tetris)) {
    kiln.run(tetris);
  }

  kiln.cleanup();
}