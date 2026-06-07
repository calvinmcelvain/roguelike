// tile.h
#ifndef TILE_H
#define TILE_H

#include <unordered_map>

#include "coordinate.h"

/**
 * @brief Enum for tile types
 *
 */
enum class TileType { Wall, Floor, Door };

/**
 * @brief attributes for each tile type, used in a static lookup table in Tile
 * class
 *
 */
struct TileAttributes {
  char symbol;
  bool walkable;
};

/**
 * @brief Tile class represents a single tile on the map, with type, position,
 * and properties.
 *
 */
class Tile {
 public:
  Tile(TileType type = TileType::Wall, Coordinate position = Coordinate(0, 0))
      : type(type), position(position) {}

  char getSymbol() const;
  bool isWalkable() const;
  TileType getType() const { return type; }
  Coordinate getPosition() const { return position; }

  static TileType charToTileType(char ch);

 private:
  TileType type;
  Coordinate position;

  // Static lookup table for tile attributes based on TileType
  static const std::unordered_map<int, TileAttributes> typeAttributes;
};

#endif