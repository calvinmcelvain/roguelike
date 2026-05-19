#include "player.h"

#include "level.h"

/**
 * @brief Construct a new Player:: Player object
 *
 * @param x Initial x position of the player
 * @param y Initial y position of the player
 * Initializes the player's position and health
 */
Player::Player(int x, int y) : position(x, y), health(100), maxHealth(100) {}

/**
 * @brief Moves the player up, down, left, right, or to a specific position.
 *
 */
void Player::moveUp() { position.y--; }
void Player::moveDown() { position.y++; }
void Player::moveLeft() { position.x--; }
void Player::moveRight() { position.x++; }
void Player::moveTo(Vector2D newPos) { position = newPos; }

/**
 * @brief Reduces the player's health by the specified damage amount. Health
 * cannot go below 0.
 *
 * @param damage The amount of damage to inflict on the player
 */
void Player::takeDamage(int damage) {
  health -= damage;
  if (health < 0) health = 0;
}

/**
 * @brief Heals the player by the specified amount. Health cannot exceed the
 * maximum health.
 *
 * @param amount The amount of health to restore
 */
void Player::heal(int amount) {
  health += amount;
  if (health > maxHealth) health = maxHealth;
}
