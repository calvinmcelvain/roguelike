#include "player.h"

#include "level.h"

Player::Player(int x, int y) : position(x, y), health(100), maxHealth(100) {}

void Player::moveUp() { position.y--; }
void Player::moveDown() { position.y++; }
void Player::moveLeft() { position.x--; }
void Player::moveRight() { position.x++; }

void Player::takeDamage(int damage) {
  health -= damage;
  if (health < 0) health = 0;
}

void Player::heal(int amount) {
  health += amount;
  if (health > maxHealth) health = maxHealth;
}
