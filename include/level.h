#ifndef LEVEL_H
#define LEVEL_H

#include <vector>

#include "vector2d.h"

class Level {
 public:
  Level(int width, int height);

  // Check if position is walkable
  bool isWalkable(Vector2D pos) const;

  // Generate level (simple box room for now)
  void generate();

  // Getters
  int getWidth() const { return width; }
  int getHeight() const { return height; }
  char getTile(Vector2D pos) const;

 private:
  int width, height;
  std::vector<std::vector<char>> tiles;
};

#endif
