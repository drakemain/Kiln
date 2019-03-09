#pragma once

#include <string>

struct WindowConfig {
  std::string title;
  unsigned int w;
  unsigned int h;

  unsigned int renderFlags = 0;
};