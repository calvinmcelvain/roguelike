#ifndef ROOM_H
#define ROOM_H

#include <vector>

#include "coordinate.h"
#include "tile.h"

struct Room {
  Coordinate position;  // Top-left corner
  int width, height;
  std::vector<std::vector<Tile>> tiles;  // Local tile grid for room
  int roomID;  // Unique identifier for graph connections
};
#endif