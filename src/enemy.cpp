#include "enemy.h"

#include <algorithm>
#include <cmath>
#include <cstdlib>

Enemy::Enemy(int x, int y, char symbol)
    : position(x, y), symbol(symbol), health(30), attackDamage(5) {}

void Enemy::moveTo(Vector2D newPos) { position = newPos; }

void Enemy::moveTowardPlayer(Vector2D playerPos) {
  // 25% chance to to not move.
  bool noMove = (std::rand() % 4) == 3;

  // make move toward player random in direction choice.
  int dir = std::rand() % 2;

  if (!noMove) {
    switch (dir) {
      // vertical dir.
      case 0:
        if (position.y < playerPos.y) {
          position.y++;
        } else if (position.y > playerPos.y) {
          position.y--;
        }
        break;

      // horizontal dir.
      case 1:
        if (position.x < playerPos.x) {
          position.x++;
        } else if (position.x > playerPos.x) {
          position.x--;
        }
        break;
    }
  }
}

void Enemy::takeDamage(int damage) { health -= damage; }
