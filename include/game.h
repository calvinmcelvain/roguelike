#ifndef GAME_H
#define GAME_H

#include <memory>
#include <vector>

#include "enemy.h"
#include "level.h"
#include "player.h"

class Enemy;

class Game {
 public:
  /**
   * @brief Construct a new Game:: Game object.
   *
   * @param width width of the game screen. By default, 175.
   * @param height height of the game screen. By default, 50.
   *
   * Initializes the player in the center of the screen, generates the level,
   * and spawns enemies.
   *
   */
  Game(int width = 175, int height = 50)
      : screenWidth(width),
        screenHeight(height),
        player(width / 2, height / 2),
        level(width, height),
        isRunning(true) {
    spawnEnemies();
  };

  /**
   * @brief Runs the main game loop.
   * Handles input, updates game state, and renders the screen at a fixed frame
   * rate.
   *
   */
  void run();

 private:
  int screenWidth, screenHeight;
  Player player;
  Level level;
  std::vector<std::unique_ptr<Enemy>> enemies;

  bool isRunning;

  /**
   * @brief Handles user input for player movement and game controls.
   * Updates the player's position based on arrow key and 'wasd' input and
   * allows quitting with 'Q'.
   *
   */
  void handleInput();

  /**
   * @brief Updates the game state - moves enemies toward the player and checks
   * for collisions.
   *
   */
  void update();

  /**
   * @brief Renders the game state. Draws the player, enemies, and UI elements
   * on the screen.
   *
   */
  void render();

  /**
   * @brief Spawns enemies in the game.
   *
   */
  void spawnEnemies();
};

#endif
