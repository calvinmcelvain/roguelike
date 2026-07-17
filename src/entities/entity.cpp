#include "entities/entity.h"

Entity::Entity(int x, int y, char symbol, int health, int speed)
    : position(x, y),
      symbol(symbol),
      health(health),
      speed(speed),
      frameCounter(0) {}
