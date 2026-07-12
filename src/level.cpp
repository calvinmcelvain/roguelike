#include "level.h"

#include <cstdlib>
#include <memory>

#include "tile.h"

Level::Level(int roomCount) : roomCount(roomCount) { generate(); }

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
  //
  // Room 0 has no incoming connection so doorPositions[0] is free to serve
  // as its exit. Every other room reserves doorPositions[0] for the back-link
  // from the previous room, so it uses doorPositions[1] as its forward exit.
  // This prevents each iteration from overwriting the previous room's
  // back-link.
  for (int i = 0; i < roomCount - 1; i++) {
    const Room& roomA = roomList.at(i);
    const Room& roomB = roomList.at(i + 1);

    int exitIdx = (i == 0) ? 0 : 1;

    if (static_cast<int>(roomA.doorPositions.size()) <= exitIdx ||
        roomB.doorPositions.empty())
      continue;

    Coordinate doorA = roomA.doorPositions[exitIdx];
    Coordinate doorB = roomB.doorPositions[0];  // all rooms enter at door[0]

    doorConnections[{i, doorA}] = {i + 1, doorB};  // A → B
    doorConnections[{i + 1, doorB}] = {i, doorA};  // B → A

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

  // Collect every Floor tile in the room. Scanning x-major means the first
  // half of the list naturally covers the left/top portion of the shape and
  // the second half covers the right/bottom — giving spatial spread.
  std::vector<Coordinate> floorTiles;
  for (int x = 0; x < Room::WIDTH; x++) {
    for (int y = 0; y < Room::HEIGHT; y++) {
      if (room.tiles[x][y].getType() == TileType::Floor) {
        floorTiles.push_back({x, y});
      }
    }
  }

  if (floorTiles.empty()) return;

  // Pick one tile from each half so enemies are spread across the room and
  // are always guaranteed to land on a valid Floor tile regardless of shape.
  std::size_t half = floorTiles.size() / 2;
  Coordinate spawn1 = floorTiles[static_cast<std::size_t>(rand()) % half];
  Coordinate spawn2 =
      floorTiles[half + static_cast<std::size_t>(rand()) % half];

  roomEnemies[roomID].push_back(
      std::make_unique<Enemy>(spawn1.x, spawn1.y, 'G'));
  roomEnemies[roomID].push_back(
      std::make_unique<Enemy>(spawn2.x, spawn2.y, 'O'));
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
