#include "game.h"

#include <ncurses.h>

#include <chrono>
#include <cstdlib>
#include <iostream>
#include <thread>

#include "enemy.h"

void Game::run() {
  printw("Roguelike Game Started! Use arrow keys to move. Press Q to quit.\n");
  printw("Press SPACE to begin...\n");

  int ch;
  do {
    ch = getch();
  } while (ch != ' ');

  const auto frame_duration = getDuration();

  while (isRunning && player.isAlive()) {
    // -------- Frame start --------
    auto start = std::chrono::high_resolution_clock::now();
    handleInput();
    update();
    render();

    // -------- Frame end --------
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = end - start;

    // TODO: Sleep to maintain consistent frame rate (there may be a better
    // solution)
    if (elapsed < frame_duration) {
      auto sleep_time =
          frame_duration -
          std::chrono::duration_cast<std::chrono::milliseconds>(elapsed);
      std::this_thread::sleep_for(sleep_time);
    }
  }

  endwin();
  std::cout << "Game Over!\n";
}

void Game::handleInput() {
  int ch = getch();

  switch (ch) {
    case KEY_UP:
    case 'w':  // Up
      player.moveUp();
      break;
    case KEY_DOWN:
    case 's':  // Down
      player.moveDown();
      break;
    case KEY_LEFT:
    case 'a':  // Left
      player.moveLeft();
      break;
    case KEY_RIGHT:
    case 'd':  // Right
      player.moveRight();
      break;
    case 'q':
    case 'Q':
      isRunning = false;
      break;
    default:
      mvprintw(2, 0, "Invalid key\n");
      break;
  }
}

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

void Game::spawnEnemies() {
  enemies.push_back(std::make_unique<Enemy>(10, 10, 'G'));
  enemies.push_back(std::make_unique<Enemy>(20, 15, 'O'));
}
