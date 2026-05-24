#ifndef ENTITY_H
#define ENTITY_H

#include <chrono>

#include "vector2d.h"

class Entity {
 public:
  Entity(int x, int y, char symbol, int health, int speed)
      : position(x, y),
        symbol(symbol),
        health(health),
        speed(speed),
        lastMoveTime(std::chrono::high_resolution_clock::now()) {};

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

 protected:
  Vector2D position;
  char symbol;
  int health;
  int speed;
  std::chrono::high_resolution_clock::time_point lastMoveTime;

  /**
   * @brief Get the speed as frequency.
   *
   * @return constexpr std::chrono::nanoseconds
   */
  constexpr std::chrono::nanoseconds getSpeedHz() {
    if (speed > 0) {
      return std::chrono::nanoseconds(1000000000 / speed);
    }

    return std::chrono::nanoseconds::max();
  };

  /**
   * @brief Move hook that moves player to new position based on their speed.
   *
   * @param newPos The potential new position to move entitiy.
   *
   */
  void moveHook(Vector2D newPos) {
    auto hook_time = std::chrono::high_resolution_clock::now();
    auto time_delta = hook_time - lastMoveTime;

    // if time since last move is >= set speed, entity can move. otherwise,
    // leave as current position.
    if (time_delta >= getSpeedHz()) {
      lastMoveTime = hook_time;
      moveTo(newPos);
    };
  };
};

#endif