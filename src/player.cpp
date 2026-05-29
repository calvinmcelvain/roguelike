#include "player.h"

#include "coordinate.h"

void Player::moveUp() { moveHook(Coordinate(position.x, position.y - 1)); }

void Player::moveDown() { moveHook(Coordinate(position.x, position.y + 1)); }

void Player::moveLeft() { moveHook(Coordinate(position.x - 1, position.y)); }

void Player::moveRight() { moveHook(Coordinate(position.x + 1, position.y)); }

void Player::takeDamage(int damage) {
  health -= damage;
  if (health < 0) health = 0;
}