#include "level.h"

#include <fstream>
#include <iostream>
#include <string>

#include "room.h"
#include "tile.h"

void Level::generate() {
  std::ifstream file;
  file.open("./assets/room.txt");

  // Check if file opened successfully
  if (!file) {
    std::cerr << "Error: Could not open file '../assets/room.txt'\n";
    return;  // Exit with error code
  }

  Room room = Room(this->roomList.size());
  std::string line;
  int y = 0;
  while (std::getline(file, line)) {
    int x = 0;
    for (char ch : line) {
      Tile tile = Tile(Tile::charToTileType(ch), Coordinate(x, y));
      room.tiles[x][y] = tile;
      room.tileList.push_back(tile);
      x++;
    }
    y++;
  }
  this->roomList.insert({room.roomID, room});
  file.close();
}