#ifndef GAME_H
#define GAME_H

#include <chrono>
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
   * @param fps frames per second of game. By default, 60.
   *
   * Initializes the player in the center of the screen, generates the level,
   * and spawns enemies.
   *
   */
  Game(int width = 175, int height = 50, int fps = 60)
      : screenWidth(width),
        screenHeight(height),
        fps(fps),
        player(width / 2, height / 2),
        level(1),
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
  const int screenWidth, screenHeight;
  const int fps;
  Player player;
  Level level;
  std::vector<std::unique_ptr<Enemy>> enemies;

  bool isRunning;

  /**
   * @brief Get the frame duraction in milliseconds.
   *
   * @return std::chrono::milliseconds
   */
  auto getDuration() const { return std::chrono::milliseconds(1000 / fps); };

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
