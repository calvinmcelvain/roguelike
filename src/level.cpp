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
    std::cerr << "Error: Could not open file './assets/room.txt'\n";
    return;
  }

  Room room = Room(this->roomList.size());
  std::string line;
  int y = 0;
  while (std::getline(file, line) && y < Room::HEIGHT) {
    int x = 0;
    for (char ch : line) {
      if (x >= Room::WIDTH) break;
      Tile tile = Tile(Tile::charToTileType(ch), Coordinate(x, y));
      room.tiles[x][y] = tile;
      x++;
    }
    y++;
  }
  this->roomList.insert({room.roomID, std::move(room)});
  file.close();
}