#include "engine/Kiln.h"
#include "kiln/Game/GameModule.h"

int main() {
  Kiln kiln;
  GameModule game;
  
  if (kiln.init(game)) {
    kiln.run(game);
  }

  kiln.cleanup();
}