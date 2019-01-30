#include "Component.h"
#include "kiln/engine/Classes/Base/headers/SpriteBase.h"

class SpriteComponent : public Component, public SpriteBase {
public:
    SpriteComponent(Entity* owner, Texture* texture);

    SpriteComponent(Entity* onwer);

    void start() override;

    void tick(float deltaTime) override;

    void setRelativePosition(int x, int y);
    void setRelativePosition(ICoordinate position);

    ICoordinate getRelativePosition() const;
    ICoordinate getWorldPosition() const;

    void render(SDL_Renderer*);

private:
    ICoordinate relativePosition;
};
