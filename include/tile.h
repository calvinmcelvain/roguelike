#ifndef TILE_H
#define TILE_H

#include "coordinate.h"

/**
 * @brief Enumeration for different types of tiles in the game, such as walls,
 * floors, doors, etc.
 *
 */
enum class TileType {
  Wall,
  Floor,
  Door,
  Corridor,
  Lava,
  Water,
  // etc.
};

/**
 * @brief Data structure representing a single tile on the game map, including
 * its type, symbol for display, and whether it's walkable. This can be extended
 * to include additional properties like entities present on the tile, loot,
 * enemies, etc.
 *
 */
struct Tile {
  TileType type;
  char symbol;
  bool walkable;
  // Optional: entities, items, blood, etc.
};

#endif