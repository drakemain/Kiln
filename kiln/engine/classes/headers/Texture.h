#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>

class Texture {
public:
  ~Texture();

  bool create(std::string filePath, SDL_Renderer* renderer);

  int getWidth() const;
  int getHeight() const;
  SDL_Texture* getTexture() const;

  void setWidth(int width);
  void setHeight(int height);

private:
  SDL_Texture* texture;
  int width;
  int height;
};