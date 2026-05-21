#include "player.h"

#include "level.h"

void Player::moveUp() { position.y--; }

void Player::moveDown() { position.y++; }

void Player::moveLeft() { position.x--; }

void Player::moveRight() { position.x++; }

void Player::takeDamage(int damage) {
  health -= damage;
  if (health < 0) health = 0;
}