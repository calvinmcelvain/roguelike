#ifndef ENTITY_H
#define ENTITY_H

#include "vector2d.h"

/**
 * @brief Abstract entity class. Implements common entity methods.
 *
 */
class Entity {
 public:
  /**
   * @brief Construct a new Entity object.
   *
   * @param x Starting column position of entity.
   * @param y Starting row position of entity.
   * @param symbol Terminal representation of entity.
   */
  Entity(int x, int y, const char symbol)
      : position(x, y), health(100), symbol(symbol) {};

  virtual ~Entity() = default;

  /**
   * @brief Get the entity health.
   *
   * @return const int
   */
  const int getHealth() { return health; };

  /**
   * @brief Get the entities symbol.
   *
   * @return const char
   */
  const char getSymbol() { return symbol; };

  /**
   * @brief Get the entity position.
   *
   * @return const Vector2D
   */
  const Vector2D getPosition() { return position; };

  /**
   * @brief Entity is alive.
   *
   * @return true If alive.
   * @return false If not alive.
   */
  const bool isAlive() { return health > 0; };

  // abstract methods.
  virtual void takeDamage() = 0;

 private:
  const char symbol;
  int health;
  Vector2D position;
};

#endif