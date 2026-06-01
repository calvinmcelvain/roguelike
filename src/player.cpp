#include "player.h"

#include "coordinate.h"

void Player::takeDamage(int damage) {
  health -= damage;
  if (health < 0) health = 0;
}