#pragma once

#include <vector>

// The SpriteComponent is the basic renderable type in Kiln.
// Any Entity that has a SpriteComponent is a RenderableEntity.
// Any RenderableEntities should be registered with the 
// SpriteManager, which will ensure that they are drawn.

// RenderableEntities will be automatically registered as long
// as the entity has been registered with the KilnModule

class SpriteManager {
public:
  SpriteManager();

  void add(class Entity* renderableEntity);
  void remove(class Entity* renderableEntity);
  void remove(class SpriteComponent* spriteComponent);
  void render(struct SDL_Renderer* renderer);

private:
  std::vector<class SpriteComponent*> sprites;
};
