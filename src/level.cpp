#include "level.h"

#include <fstream>
#include <iostream>
#include <string>

#include "room.h"
#include "tile.h"

void Level::generate() {
  std::ifstream file("../assets/room.txt");

  // Check if file opened successfully
  if (!file) {
    std::cerr << "Error: Could not open file '../assets/room.txt'\n";
    return;  // Exit with error code
  }

  Room room = Room(this->roomList.size());
  std::string line;
  int y = 0;
  while (std::getline(file, line)) {
    std::vector<char> row;
    int x = 0;
    for (char ch : line) {
      room.tiles[x][y] = Tile(Tile::charToTileType(ch), Coordinate(x, y));
      x++;
    }
    y++;
  }
  this->roomList[room.roomID] = room;
}