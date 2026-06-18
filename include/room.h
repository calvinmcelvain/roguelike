#ifndef ROOM_H
#define ROOM_H

#include <vector>

#include "coordinate.h"
#include "tile.h"

struct Room {
  static constexpr int WIDTH = 175,
                       HEIGHT = 50;
  int roomID;                        // Unique identifier for graph connections
  std::vector<std::vector<Tile>> tiles;  // Dynamic 2D tile grid
  
  Room(int id) : roomID(id), tiles(WIDTH, std::vector<Tile>(HEIGHT)) {}
  
  // Move semantics for efficient transfer
  Room(Room&&) = default;
  Room& operator=(Room&&) = default;
  
  // Prevent copying due to large tile grid
  Room(const Room&) = delete;
  Room& operator=(const Room&) = delete;
};
#endif