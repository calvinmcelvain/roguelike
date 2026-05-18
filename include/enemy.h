#ifndef ENEMY_H
#define ENEMY_H

#include "vector2d.h"

class Enemy {
 public:
  Enemy(int x, int y, char symbol = 'E');

  // Movement
  void moveTo(Vector2D newPos);
  void moveTowardPlayer(Vector2D playerPos);

  // Getters
  Vector2D getPosition() const { return position; }
  char getSymbol() const { return symbol; }
  int getHealth() const { return health; }
  bool isAlive() const { return health > 0; }

  // Combat
  void takeDamage(int damage);
  int getAttackDamage() const { return attackDamage; }

 private:
  Vector2D position;
  char symbol;
  int health;
  int attackDamage;
};

#endif
