#ifndef ENTITY_H
#define ENTITY_H

#include <chrono>

#include "coordinate.h"

class Entity {
 public:
  Entity(int x, int y, char symbol, int health, int speed)
      : position(x, y), symbol(symbol), health(health), speed(speed) {};

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
   * @return const Coordinate
   */
  Coordinate getPosition() const { return position; };

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
  void moveTo(Coordinate newPos) { position = newPos; };

  // abstract methods.
  virtual void takeDamage(int damage) = 0;

 protected:
  Coordinate position;
  char symbol;
  int health;
  int speed;
  int frameCounter;

  /**
   * @brief Get the speed as frequency.
   *
   * @return std::chrono::nanoseconds
   */
  std::chrono::nanoseconds getSpeedHz() const {
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
  void moveHook(Coordinate newPos) {
    // when move hook is called, we assume a frame.
    frameCounter += 1;

    if (frameCounter % speed == 0) {
      frameCounter = 0;  // reset counter.
      moveTo(newPos);
    };
  };
};

#endif