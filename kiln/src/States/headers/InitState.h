#include "State.h"
#include "kiln/src/Kiln.h"
#include "kiln/src/classes/headers/Sprite.h"

class InitState : public State, public Base {
public:
  InitState(CoreManagement& coreManagement);

  void init() override;
  void cleanup() override;

  void pause() override;
  void resume() override;

  void handleEvents() override;
  void tick(float deltaTime) override;
  void render() override;

private:
  float uptime;
  CoreManagement& coreManagement;
  Sprite testSprite;
};