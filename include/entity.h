#ifndef ENTITY_H
#define ENTITY_H

#include "vector2d.h"

class Entity {
 public:
  Entity(int x, int y, char symbol, int health)
      : position(x, y), symbol(symbol), health(health) {};

  virtual ~Entity() = default;

  /**
   * @brief Get the entity health.
   *
   * @return const int
   */
  int getHealth() const { return health; };

  /**
   * @brief Get the entities symbol.
   *
   * @return const char
   */
  char getSymbol() const { return symbol; };

  /**
   * @brief Get the entity position.
   *
   * @return const Vector2D
   */
  Vector2D getPosition() const { return position; };

  /**
   * @brief Entity is alive.
   *
   * @return bool
   */
  bool isAlive() const { return health > 0; };

  /**
   * @brief Move entity to new position.
   *
   * @param newPos Corrdinates of new position.
   */
  void moveTo(Vector2D newPos) { position = newPos; };

  // abstract methods.
  virtual void takeDamage(int damage) = 0;

 private:
  Vector2D position;
  char symbol;
  int health;
};

#endif