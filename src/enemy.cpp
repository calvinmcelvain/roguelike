#include "enemy.h"

#include <algorithm>
#include <cmath>
#include <cstdlib>

#include "vector2d.h"

void Enemy::moveTowardPlayer(Vector2D playerPos) {
  bool needsX = position.x != playerPos.x;
  bool needsY = position.y != playerPos.y;

  int newX = position.x + (position.x < playerPos.x ? 1 : -1);
  int newY = position.y + (position.y < playerPos.y ? 1 : -1);

  Vector2D newPos = position;
  if (needsX && needsY) {
    // only randomly choose when both movements can be made.
    if (std::rand() % 2 == 0) {
      newPos.y = newY;
    } else {
      newPos.x = newX;
    }
  } else if (needsX) {
    newPos.x = newX;
  } else if (needsY) {
    newPos.y = newY;
  }

  moveHook(newPos);
}

void Enemy::takeDamage(int damage) { health -= damage; }
