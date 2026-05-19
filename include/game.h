#ifndef GAME_H
#define GAME_H

#include <memory>
#include <vector>

#include "enemy.h"
#include "level.h"
#include "player.h"
#include "terminal_graphics.h"

class Enemy;

class Game {
 public:
  Game(int width = 80, int height = 24);

  // Main game loop
  void run();

 private:
  int screenWidth, screenHeight;
  Player player;
  Level level;
  TerminalGraphics graphics;
  std::vector<std::unique_ptr<Enemy>> enemies;

  bool isRunning;

  // Game phases
  void handleInput();
  void update();
  void render();
  void spawnEnemies();
};

#endif
