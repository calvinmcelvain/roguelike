#include "tile.h"

void Tile::generateTile(char symbol, Coordinate position) {
  this->symbol = symbol;
  this->position = position;
  walkable = (symbol == ' ');  // Only space is walkable
}
