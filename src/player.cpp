#include "player.h"

#include "vector2d.h"

void Player::moveUp() { moveHook(Vector2D(position.x, position.y - 1)); }

void Player::moveDown() { moveHook(Vector2D(position.x, position.y + 1)); }

void Player::moveLeft() { moveHook(Vector2D(position.x - 1, position.y)); }

void Player::moveRight() { moveHook(Vector2D(position.x + 1, position.y)); }

void Player::takeDamage(int damage) {
  health -= damage;
  if (health < 0) health = 0;
}