#ifndef ROOM_H
#define ROOM_H

#include <vector>

#include "coordinate.h"
#include "tile.h"

/**
 * @brief Describes the floor-plan shape used when procedurally generating a
 * room.
 *
 * All shapes fit within the Room::WIDTH × Room::HEIGHT grid. Tiles outside
 * the carved region are set to TileType::Void.
 */
enum class RoomShape {
  Rectangular,  ///< Full 175×50 box.
  LShape,       ///< Left column + bottom-right rectangle.
  TShape,       ///< Full-width top bar + centred vertical stem.
  CrossShape,   ///< Full-width horizontal band + full-height vertical band.
};

/**
 * @brief Represents a single room on the game map.
 *
 * A Room owns a fixed-size 2-D tile grid (WIDTH × HEIGHT). Tiles outside the
 * shaped floor area are TileType::Void. Door positions on the room's perimeter
 * walls are tracked in doorPositions so Level can wire room connections.
 */
struct Room {
  static constexpr int WIDTH = 175;  ///< Tile columns per room.
  static constexpr int HEIGHT = 50;  ///< Tile rows per room.

  int roomID;                             ///< Unique identifier for this room.
  std::vector<std::vector<Tile>> tiles;   ///< Tile grid, indexed [x][y].
  std::vector<Coordinate> doorPositions;  ///< Wall positions that are doors.

  /// True when the tile is inside the player's current FoV. Recomputed each
  /// frame by Level::updateVisibility. Indexed [x][y].
  std::vector<std::vector<bool>> visible;

  /// True once the tile has ever been visible. Persists across frames and
  /// room re-entries so the map is "remembered" once seen. Indexed [x][y].
  std::vector<std::vector<bool>> explored;

  /**
   * @brief Construct an empty Room filled with default Wall tiles.
   *
   * @param id Unique room identifier.
   */
  Room(int id);

  /**
   * @brief Procedurally generate a Room with the given shape.
   *
   * Fills the grid with Void, carves a floor region matching @p shape, converts
   * perimeter floors to Walls, and places doors at well-known wall positions.
   *
   * @param roomID Unique identifier assigned to the generated room.
   * @param shape  Floor-plan shape to carve.
   * @return A fully populated Room ready to be added to a Level.
   */
  static Room generate(int roomID, RoomShape shape);

  /**
   * @brief Reset every cell in the visible grid to false.
   *
   * Called at the start of each visibility pass before the new FoV cells
   * are marked visible. The explored grid is left untouched.
   */
  void clearVisible();

  /**
   * @brief Bounds-checked visibility query.
   *
   * @param x Column.
   * @param y Row.
   * @return bool True if the tile is inside the current FoV. False if out
   * of bounds.
   */
  bool isVisible(int x, int y) const;

  /**
   * @brief Bounds-checked explored query.
   *
   * @param x Column.
   * @param y Row.
   * @return bool True if the tile has been seen at least once. False if
   * out of bounds.
   */
  bool isExplored(int x, int y) const;

  /**
   * @brief Mark a tile as currently visible and permanently explored.
   *
   * No-op if (x, y) falls outside the room grid so callers may pass raw
   * FoV coordinates without clamping first.
   *
   * @param x Column.
   * @param y Row.
   */
  void reveal(int x, int y);

  Room(Room&&) = default;
  Room& operator=(Room&&) = default;

  Room(const Room&) = delete;
  Room& operator=(const Room&) = delete;
};

#endif