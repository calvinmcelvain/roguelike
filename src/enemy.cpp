#include "enemy.h"

#include <algorithm>
#include <cmath>

Enemy::Enemy(int x, int y, char symbol)
    : position(x, y), symbol(symbol), health(30), attackDamage(5) {}

void Enemy::moveTo(Vector2D newPos) { position = newPos; }

void Enemy::moveTowardPlayer(Vector2D playerPos) {
  // Simple AI: move one step toward player
  if (position.x < playerPos.x)
    position.x++;
  else if (position.x > playerPos.x)
    position.x--;

  if (position.y < playerPos.y)
    position.y++;
  else if (position.y > playerPos.y)
    position.y--;
}

void Enemy::takeDamage(int damage) { health -= damage; }
