#ifndef LEVEL_H
#define LEVEL_H

#include <vector>

#include "coordinate.h"

class Level {
 public:
  Level(int width, int height) : width(width), height(height) { generate(); };

  // Check if position is walkable
  bool isWalkable(Coordinate pos) const;

  // Generate level (simple box room for now)
  void generate();

  // Getters
  int getWidth() const { return width; }
  int getHeight() const { return height; }
  char getTile(Coordinate pos) const;

 private:
  int width, height;
  std::vector<std::vector<char>> tiles;
};

#endif
