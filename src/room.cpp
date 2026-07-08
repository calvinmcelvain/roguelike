#include "room.h"

// Have to create this namespace to keep the helper function private to this
// file, since it's only used in Room::generate().
namespace {

// Helper function to fill a rectangular region with Floor tiles.
void fillRect(Room& room, int x1, int y1, int x2, int y2) {
  for (int x = x1; x <= x2; x++)
    for (int y = y1; y <= y2; y++)
      room.tiles[x][y] = Tile(TileType::Floor, {x, y});
}

}  // namespace

Room Room::generate(int roomID, RoomShape shape) {
  Room room(roomID);

  // Fill entire grid with Void.
  for (int x = 0; x < WIDTH; x++)
    for (int y = 0; y < HEIGHT; y++)
      room.tiles[x][y] = Tile(TileType::Void, {x, y});

  // Carve floor regions based on shape.
  //
  //  Rectangular : full 175x50 box
  //  LShape      : left column (x 0..89, full height)
  //                + bottom-right rectangle (x 90..174, y 25..49)
  //  TShape      : horizontal top bar (full width, y 0..24)
  //                + vertical stem (x 58..116, y 25..49)
  //  CrossShape  : horizontal band (full width, y 12..37)
  //                + vertical band (x 58..116, full height)
  switch (shape) {
    case RoomShape::Rectangular:
      fillRect(room, 0, 0, WIDTH - 1, HEIGHT - 1);
      break;
    case RoomShape::LShape:
      fillRect(room, 0, 0, 89, HEIGHT - 1);
      fillRect(room, 90, HEIGHT / 2, WIDTH - 1, HEIGHT - 1);
      break;
    case RoomShape::TShape:
      fillRect(room, 0, 0, WIDTH - 1, HEIGHT / 2);
      fillRect(room, WIDTH / 3, HEIGHT / 2 + 1, (WIDTH * 2) / 3, HEIGHT - 1);
      break;
    case RoomShape::CrossShape:
      fillRect(room, 0, HEIGHT / 4, WIDTH - 1, (HEIGHT * 3) / 4);
      fillRect(room, WIDTH / 3, 0, (WIDTH * 2) / 3, HEIGHT - 1);
      break;
  }

  // Snapshot the carved regions, then convert any Floor tile that
  // borders a Void (or is out-of-bounds) into a Wall tile.
  // snapshot is a 2D vector of TileType, so we can check the original state of
  // the room while modifying it.
  std::vector<std::vector<TileType>> snapshot(WIDTH,
                                              std::vector<TileType>(HEIGHT));
  for (int x = 0; x < WIDTH; x++)
    for (int y = 0; y < HEIGHT; y++)
      snapshot[x][y] = room.tiles[x][y].getType();

  // Helper lambda to check if a coordinate is out-of-bounds or is a Void tile.
  auto isVoidOrOOB = [&](int x, int y) -> bool {
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) return true;
    return snapshot[x][y] == TileType::Void;
  };

  for (int x = 0; x < WIDTH; x++) {
    for (int y = 0; y < HEIGHT; y++) {
      if (snapshot[x][y] == TileType::Floor) {
        if (isVoidOrOOB(x - 1, y) || isVoidOrOOB(x + 1, y) ||
            isVoidOrOOB(x, y - 1) || isVoidOrOOB(x, y + 1)) {
          room.tiles[x][y] = Tile(TileType::Wall, {x, y});
        }
      }
    }
  }

  // Place doors at well-known wall positions for each shape.
  // Each position is guaranteed to land on a perimeter Wall tile.
  // TODO: Consider adding a randomization factor to door placement, so that not
  // every room of the same shape has doors in the same locations.
  //
  //  Rectangular : N=top-center, S=bottom-center, W=left-mid, E=right-mid
  //  LShape      : top of left arm, left mid, right of bottom-right arm,
  //                bottom of bottom-right arm
  //  TShape      : top-center, left-mid of top bar, right-mid of top bar,
  //                bottom of stem
  //  CrossShape  : top of vertical band, bottom, left of horizontal band,
  //                right
  std::vector<Coordinate> doorCoords;
  switch (shape) {
    case RoomShape::Rectangular:
      doorCoords = {{WIDTH / 2, 0},
                    {WIDTH / 2, HEIGHT - 1},
                    {0, HEIGHT / 2},
                    {WIDTH - 1, HEIGHT / 2}};
      break;
    case RoomShape::LShape:
      doorCoords = {{44, 0},
                    {0, HEIGHT / 2},
                    {WIDTH - 1, (HEIGHT * 3) / 4},
                    {132, HEIGHT - 1}};
      break;
    case RoomShape::TShape:
      doorCoords = {{WIDTH / 2, 0},
                    {0, HEIGHT / 4},
                    {WIDTH - 1, HEIGHT / 4},
                    {WIDTH / 2, HEIGHT - 1}};
      break;
    case RoomShape::CrossShape:
      doorCoords = {{WIDTH / 2, 0},
                    {WIDTH / 2, HEIGHT - 1},
                    {0, HEIGHT / 2},
                    {WIDTH - 1, HEIGHT / 2}};
      break;
  }

  for (auto& coord : doorCoords) {
    room.tiles[coord.x][coord.y] = Tile(TileType::Door, coord);
    room.doorPositions.push_back(coord);
  }

  return room;
}
