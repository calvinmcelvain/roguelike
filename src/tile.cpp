#include "tile.h"

// Define all tile types and their attributes in ONE place
const std::unordered_map<int, TileAttributes> Tile::typeAttributes = {
    {static_cast<int>(TileType::Wall), {'#', false}},
    {static_cast<int>(TileType::Floor), {'.', true}},
    {static_cast<int>(TileType::Door), {'+', true}},
};

char Tile::getSymbol() const {
  return typeAttributes.at(static_cast<int>(type)).symbol;
}

bool Tile::isWalkable() const {
  return typeAttributes.at(static_cast<int>(type)).walkable;
}
