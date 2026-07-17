#ifndef ENEMY_H
#define ENEMY_H

#include "core/coordinate.h"
#include "entities/entity.h"
#include "entities/fov.h"

class Enemy : public Entity {
 public:
  /**
   * @brief Construct a new Enemy object.
   *
   * @param x Starting column position of enemy.
   * @param y Starting row position of enemy.
   * @param symbol Terminal representation of enemy. By default, 'E'.
   * @param health Starting health of enemy. By default, 100.
   * @param speed Frames per move. For example, speed = 2, means an enemy can
   * move per every 2 frames/renders. By default, equal to 10.
   * @param attackDamage The attack damage of enemy. By default, 10.
   * @param attackFOV The FOV of the enemy. By default, an ellipse FOV w/
   * rx = 20, ry = 10.
   */
  Enemy(int x, int y, char symbol = 'E', int health = 100, int speed = 10,
        int attackDamage = 10, FOV attackFOV = ellipseFOV(20, 10));

  /**
   * @brief Get the enemy's attack damage.
   *
   * @return int
   */
  int getAttackDamage() const { return attackDamage; };

  /**
   * @brief Reduce enemy health by damage amount.
   *
   * @param damage Amount of damage to apply.
   */
  void takeDamage(int damage) override;

  /**
   * @brief Move one step toward the player's position.
   *
   * @param playerPos Current position of the player.
   */
  void moveTowardPlayer(Coordinate playerPos);

 private:
  int attackDamage;
  FOV attackFOV;
};

#endif
