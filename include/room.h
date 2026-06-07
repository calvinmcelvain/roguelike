#ifndef ROOM_H
#define ROOM_H

#include <vector>

#include "coordinate.h"
#include "tile.h"

struct Room {
  static constexpr int WIDTH = 175,
                       HEIGHT = 50;  // Needs to be static to be used in tile
                                     // grid declaration (compile time constant)
  Tile tiles[WIDTH][HEIGHT];  // Local tile grid for room
  int roomID;                 // Unique identifier for graph connections
  Room(int id) : roomID(id) {}
};
#endif