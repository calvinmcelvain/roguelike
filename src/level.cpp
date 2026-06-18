#include "level.h"

#include <fstream>
#include <iostream>
#include <stdexcept>
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

const Room& Level::getCurrentRoom() const {
  if (!hasRoom(currentRoomID)) {
    throw std::out_of_range("Current room ID does not exist");
  }
  return roomList.at(currentRoomID);
}

void Level::addRoom(Room&& room) {
  this->roomList.insert({room.roomID, std::move(room)});
}