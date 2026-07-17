#include "entities/player.h"

#include "core/coordinate.h"

Player::Player(int x, int y, int health, int speed)
    : Entity(x, y, '@', health, speed), maxHealth(health) {}

void Player::takeDamage(int damage) {
  health -= damage;
  if (health < 0) health = 0;
}