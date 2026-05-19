#ifndef PLAYER_H
#define PLAYER_H

#include "vector2d.h"

class Player {
 public:
  Player(int x, int y);

  // Movement
  void moveUp();
  void moveDown();
  void moveLeft();
  void moveRight();
  void moveTo(Vector2D newPos);

  // Getters
  Vector2D getPosition() const { return position; }
  int getHealth() const { return health; }
  int getMaxHealth() const { return maxHealth; }

  // Combat
  void takeDamage(int damage);
  void heal(int amount);

 private:
  Vector2D position;
  int health;
  int maxHealth;
};

#endif
