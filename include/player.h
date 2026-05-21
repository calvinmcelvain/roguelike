#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"
#include "vector2d.h"

class Player : public Entity {
 public:
  /**
   * @brief Construct a new Player object.
   *
   * @param x Starting column position of player.
   * @param y Starting row position of player.
   * @param health Starting health of player.
   */
  Player(int x, int y, int health = 100)
      : Entity(x, y, '@', health), maxHealth(health) {};

  /**
   * @brief Moves player up one row.
   *
   */
  void moveUp();

  /**
   * @brief Moves player down one row.
   *
   */
  void moveDown();

  /**
   * @brief Moves player right one column.
   *
   */
  void moveLeft();

  /**
   * @brief Moves player left one column.
   *
   */
  void moveRight();

  /**
   * @brief Get the initial max health of player.
   *
   * @return int
   */
  int getMaxHealth() const { return maxHealth; }

  /**
   * @brief Reduce player health by damage amount.
   *
   * @param damage Amount of damage to apply.
   */
  void takeDamage(int damage) override;

 private:
  int maxHealth;
};

#endif
