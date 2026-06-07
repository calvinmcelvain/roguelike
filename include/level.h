#ifndef LEVEL_H
#define LEVEL_H

#include <map>
#include <vector>

#include "coordinate.h"
#include "room.h"

/**
 * @brief Level class represents the game map/level, including the layout of
 * rooms and doors.
 *
 */
class Level {
 public:
  Level(int roomCount) : roomCount(roomCount) { generate(); };

  void addRoom(Room room);

  // Generate level (simple box room for now)
  void generate();

  // Getters
  int getRoomCount() const { return roomCount; }
  // char getTile(Coordinate pos) const;

 private:
  int roomCount;
  std::map<int, Room> roomList;  // Map of roomID to Room object
  std::vector<std::vector<int>> roomConnections;  // adjacency list of rooms
};

#endif
