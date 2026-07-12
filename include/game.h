#ifndef GAME_H
#define GAME_H

#include <chrono>
#include <memory>
#include <vector>

#include "enemy.h"
#include "layers/debug_layer.h"
#include "layers/entity_layer.h"
#include "layers/hud_layer.h"
#include "layers/map_layer.h"
#include "level.h"
#include "player.h"
#include "renderer.h"

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
   * spawns enemies, and builds the render layer stack.
   *
   */
  Game(int width = 175, int height = 50, int fps = 60);

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
  double currentFps;
  Player player;
  Level level;
  std::vector<std::unique_ptr<Enemy>> enemies;

  bool isRunning;
  Renderer renderer;

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

  /**
   * @brief Transition the player to a connected room via a door.
   *
   * Persists the current room's enemies, loads the destination room's enemies,
   * updates the active room, and places the player one tile inward from the
   * destination door.
   *
   * @param conn The door connection describing the destination.
   */
  void transitionRoom(const DoorConnection& conn);
};

#endif
