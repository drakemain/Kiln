#include "../headers/SpriteManager.h"
#include "../../Classes/Entity/headers/Entity.h"
#include "../../Classes/Components/headers/SpriteComponent.h"

SpriteManager::SpriteManager() {}

void SpriteManager::add(Entity* entity) {
  std::vector<SpriteComponent*> sprites;
  
  entity->getComponentsByType<SpriteComponent*>(sprites);
  
  for (SpriteComponent* sprite : sprites) {
    this->sprites.push_back(sprite);
  }
}

void SpriteManager::remove(Entity* entity) {
  std::vector<SpriteComponent*> entitySprites;
  entity->getComponentsByType<SpriteComponent*>(entitySprites);

  for (SpriteComponent* sprite : entitySprites) {
    this->remove(sprite);
  }
}

void SpriteManager::remove(SpriteComponent* sprite) {
  for(auto iter = this->sprites.begin(); iter != this->sprites.end(); ++iter) {
    if (*iter == sprite) {
      this->sprites.erase(iter);
      break;
    }
  }
}

void SpriteManager::render(SDL_Renderer* renderer) {
  for (SpriteComponent* sprite : this->sprites) {
    sprite->render(renderer);
  }
}