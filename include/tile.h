#ifndef TILE_H
#define TILE_H

#include "coordinate.h"

class Tile {
 public:
  Tile(char symbol = '#', bool walkable = false,
       Coordinate position = Coordinate(0, 0))
      : symbol(symbol), walkable(walkable), position(position) {};

  char getSymbol() const { return symbol; }
  bool isWalkable() const { return walkable; }
  Coordinate getPosition() const { return position; }

 private:
  char symbol;
  bool walkable;
  Coordinate position;
  void generateTile(char symbol, Coordinate position);
};

#endif