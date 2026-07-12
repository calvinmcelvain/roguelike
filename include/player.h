#ifndef PLAYER_H
#define PLAYER_H

#include "coordinate.h"
#include "entity.h"

class Player : public Entity {
 public:
  /**
   * @brief Construct a new Player object.
   *
   * @param x Starting column position of player.
   * @param y Starting row position of player.
   * @param health Starting health of player.
   * @param speed Frames per move. For example, speed = 2, means a player can
   * move per every 2 frames/renders. By default, equal to 1.
   */
  Player(int x, int y, int health = 100, int speed = 1);

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
