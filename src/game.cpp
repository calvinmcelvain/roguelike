#include "game.h"

#include <ncurses.h>

#include <chrono>
#include <cstdlib>
#include <iostream>
#include <thread>

#include "enemy.h"

/**
 * @brief Construct a new Game:: Game object.
 *
 * @param width width of the game screen
 * @param height height of the game screen
 * Initializes the player in the center of the screen, generates the level, and
 * spawns enemies.
 *
 */
Game::Game(int width, int height)
    : screenWidth(width),
      screenHeight(height),
      player(width / 2, height / 2),
      level(width, height),
      isRunning(true) {
  spawnEnemies();
}

/**
 * @brief Runs the main game loop.
 * Handles input, updates game state, and renders the screen at a fixed frame
 * rate.
 *
 */
void Game::run() {
  printw("Roguelike Game Started! Use arrow keys to move. Press Q to quit.\n");
  printw("Press any key to begin...\n");

  box(stdscr, 0, 0);
  refresh();

  // Set frame rate control variables
  const int FPS = 20;
  const int FRAME_TIME = 1000 / FPS;

  while (isRunning && player.isAlive()) {
    // -------- Frame start --------
    auto start = std::chrono::high_resolution_clock::now();
    handleInput();
    update();
    render();

    // -------- Frame end --------
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed =
        std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
            .count();

    // TODO: Sleep to maintain consistent frame rate (there may be a better
    // solution)
    if (elapsed < FRAME_TIME) {
      std::this_thread::sleep_for(
          std::chrono::milliseconds(FRAME_TIME - elapsed));
    }
  }

  endwin();
  std::cout << "Game Over!\n";
}

/**
 * @brief Handles user input for player movement and game controls.
 * Updates the player's position based on arrow key and 'wasd' input and allows
 * quitting with 'Q'.
 *
 */
void Game::handleInput() {
  int ch = getch();
  Vector2D newPos = player.getPosition();

  switch (ch) {
    case KEY_UP:
    case 'w':  // Up
      newPos.y--;
      break;
    case KEY_DOWN:
    case 's':  // Down
      newPos.y++;
      break;
    case KEY_LEFT:
    case 'a':  // Left
      newPos.x--;
      break;
    case KEY_RIGHT:
    case 'd':  // Right
      newPos.x++;
      break;
    case 'q':
    case 'Q':
      isRunning = false;
      break;
    default:
      mvprintw(2, 0, "Invalid key\n");
      break;
  }

  // only allow movement if player alive.
  if (player.isAlive()) {
    player.moveTo(newPos);
  }
}

/**
 * @brief Updates the game state - moves enemies toward the player and checks
 * for collisions.
 *
 */
void Game::update() {
  // Move enemies toward player
  Vector2D playerPos = player.getPosition();

  for (auto& enemy : enemies) {
    if (enemy->isAlive()) {
      enemy->moveTowardPlayer(playerPos);

      // Check collision with player
      if (enemy->getPosition() == playerPos) {
        player.takeDamage(enemy->getAttackDamage());
      }
    }
  }
}

/**
 * @brief Renders the game state. Draws the player, enemies, and UI elements on
 * the screen.
 *
 */
void Game::render() {
  clear();
  box(stdscr, 0, 0);

  // Draw player... if alive.
  if (player.isAlive()) {
    Vector2D playerPos = player.getPosition();
    mvaddch(playerPos.y, playerPos.x, '@');
  }

  // Draw enemies
  for (const auto& enemy : enemies) {
    if (enemy->isAlive()) {
      Vector2D enemyPos = enemy->getPosition();
      mvaddch(enemyPos.y, enemyPos.x, enemy->getSymbol());
    }
  }

  // Draw UI
  mvprintw(0, 0, "HP: %d/%d", player.getHealth(), player.getMaxHealth());

  refresh();
}

/**
 * @brief Spawns enemies in the game.
 *
 */
void Game::spawnEnemies() {
  enemies.push_back(std::make_unique<Enemy>(10, 10, 'G'));
  enemies.push_back(std::make_unique<Enemy>(20, 15, 'O'));
}
