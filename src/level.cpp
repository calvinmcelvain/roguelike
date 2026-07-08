#include "level.h"

#include <cstdlib>
#include <memory>

#include "tile.h"

namespace {

// Scan from (startX, startY) and return the first Floor tile in the room.
// Wraps around the grid if needed. Falls back to the start position.
Coordinate findFloorTile(const Room& room, int startX, int startY) {
  for (int dy = 0; dy < Room::HEIGHT; dy++) {
    for (int dx = 0; dx < Room::WIDTH; dx++) {
      int x = (startX + dx) % Room::WIDTH;
      int y = (startY + dy) % Room::HEIGHT;
      if (room.tiles[x][y].getType() == TileType::Floor) {
        return {x, y};
      }
    }
  }
  return {startX, startY};
}

}  // namespace

void Level::addRoom(Room room) {
  int id = room.roomID;
  roomList.insert({id, std::move(room)});
}

void Level::generate() {
  // Generate rooms, each with a randomly chosen floor-plan shape.
  const RoomShape shapes[] = {RoomShape::Rectangular, RoomShape::LShape,
                               RoomShape::TShape, RoomShape::CrossShape};
  const int shapeCount = 4;

  for (int i = 0; i < roomCount; i++) {
    RoomShape shape = shapes[rand() % shapeCount];
    addRoom(Room::generate(i, shape));
    roomConnections.push_back({});
  }

  // Wire doors in a chain: room 0 ↔ 1 ↔ 2 ↔ … ↔ (N-1).
  // Each adjacent pair is linked via doorPositions[0] on both sides.
  // Remaining doors on each room are cosmetic and currently unlinked.
  for (int i = 0; i < roomCount - 1; i++) {
    const Room& roomA = roomList.at(i);
    const Room& roomB = roomList.at(i + 1);

    if (roomA.doorPositions.empty() || roomB.doorPositions.empty()) continue;

    Coordinate doorA = roomA.doorPositions[0];
    Coordinate doorB = roomB.doorPositions[0];

    doorConnections[{i, doorA}] = {i + 1, doorB};      // A → B
    doorConnections[{i + 1, doorB}] = {i, doorA};      // B → A

    roomConnections[i].push_back(i + 1);
    roomConnections[i + 1].push_back(i);
  }
}

const DoorConnection* Level::getDoorConnection(int roomID,
                                               Coordinate doorPos) const {
  auto it = doorConnections.find({roomID, doorPos});
  if (it != doorConnections.end()) return &it->second;
  return nullptr;
}

void Level::spawnEnemiesForRoom(int roomID) {
  const Room& room = roomList.at(roomID);

  // Spawn 2 enemies at floor tiles in the first and third quadrants so
  // they are spread across the room regardless of shape.
  Coordinate spawn1 = findFloorTile(room, Room::WIDTH / 4, Room::HEIGHT / 4);
  Coordinate spawn2 =
      findFloorTile(room, (Room::WIDTH * 3) / 4, (Room::HEIGHT * 3) / 4);

  roomEnemies[roomID].push_back(std::make_unique<Enemy>(spawn1.x, spawn1.y, 'G'));
  roomEnemies[roomID].push_back(std::make_unique<Enemy>(spawn2.x, spawn2.y, 'O'));
}

void Level::loadInitialEnemies(
    std::vector<std::unique_ptr<Enemy>>& activeEnemies) {
  if (!roomVisited[0]) {
    roomVisited[0] = true;
    spawnEnemiesForRoom(0);
  }
  activeEnemies = std::move(roomEnemies[0]);
}

void Level::transitionEnemies(
    int fromRoomID, int toRoomID,
    std::vector<std::unique_ptr<Enemy>>& activeEnemies) {
  // Park the current room's enemies back into storage.
  roomEnemies[fromRoomID] = std::move(activeEnemies);

  // Generate enemies for the destination room on first visit.
  if (!roomVisited[toRoomID]) {
    roomVisited[toRoomID] = true;
    spawnEnemiesForRoom(toRoomID);
  }

  // Hand the destination room's enemies to the caller.
  activeEnemies = std::move(roomEnemies[toRoomID]);
}

