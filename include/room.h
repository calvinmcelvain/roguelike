#ifndef ROOM_H
#define ROOM_H

#include "coordinate.h"

struct Room {
  Coordinate position;  // Top-left corner
  int width, height;
  std::vector<std::vector<Tile>> tiles;  // Local tile grid for room
  int roomID;        // Unique identifier for graph connections
  std::string name;  // Optional: descriptive name
};
#endif