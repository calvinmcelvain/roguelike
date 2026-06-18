#ifndef ROOM_H
#define ROOM_H

#include <vector>

#include "coordinate.h"
#include "tile.h"

struct Room {
  static constexpr int WIDTH = 175,
                       HEIGHT = 50;
  int roomID;
  std::vector<std::vector<Tile>> tiles;
  
  Room(int id) : roomID(id), tiles(WIDTH, std::vector<Tile>(HEIGHT)) {}
  
  Room(Room&&) = default;
  Room& operator=(Room&&) = default;
  
  Room(const Room&) = delete;
  Room& operator=(const Room&) = delete;
};
#endif