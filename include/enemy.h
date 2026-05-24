#ifndef ENEMY_H
#define ENEMY_H

#include "entity.h"
#include "vector2d.h"

class Enemy : public Entity {
 public:
  /**
   * @brief Construct a new Enemy object.
   *
   * @param x Starting column position of enemy.
   * @param y Starting row position of enemy.
   * @param symbol Terminal representation of enemy. By default, 'E'.
   * @param health Starting health of enemy. By default, 100.
   * @param speed Moves per second. For example, if speed = 60 → can move every
   frame at 60fps. By default, 10.
   * @param attackDamage The attack damage of enemy. By default, 10.
   */
  Enemy(int x, int y, char symbol = 'E', int health = 100, int speed = 10,
        int attackDamage = 10)
      : Entity(x, y, symbol, health, speed), attackDamage(attackDamage) {};

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
  void moveTowardPlayer(Vector2D playerPos);

 private:
  int attackDamage;
};

#endif
