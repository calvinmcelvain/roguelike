#ifndef ROOM_H
#define ROOM_H

#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "vector2d.h"

const int MAX_WIDTH = 100;
const int MAX_HEIGHT = 100;

class Room {
 public:
  Room(std::string layout, int difficulty = 1);

  // Check if position is walkable
  bool isWalkable(Vector2D pos) const;

  // Generate room (simple box room for now)
  void generate();

  // Getters
  int getWidth() const { return width; }
  int getHeight() const { return height; }
  char getTile(Vector2D pos) const;

 private:
  int width, height;
  char roomMap[MAX_WIDTH][MAX_HEIGHT] = {
      0};  // Max room size of 100x100 for simplicity
  char delimiter = '|';
};

#endif