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

  this->level.generate();
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
  Coordinate newPlayerPos = player.getPosition();

  switch (ch) {
    case KEY_UP:
    case 'w':  // Up
      newPlayerPos.y -= 1;
      break;
    case KEY_DOWN:
    case 's':  // Down
      newPlayerPos.y += 1;
      break;
    case KEY_LEFT:
    case 'a':  // Left
      newPlayerPos.x -= 1;
      break;
    case KEY_RIGHT:
    case 'd':  // Right
      newPlayerPos.x += 1;
      break;
    case 'q':
    case 'Q':
      isRunning = false;
      break;
    default:
      mvprintw(2, 0, "Invalid key\n");
      break;
  }
  if (newPlayerPos.x >= 0 && newPlayerPos.x < Room::WIDTH &&
      newPlayerPos.y >= 0 && newPlayerPos.y < Room::HEIGHT &&
      level.getCurrentRoom()
          .tiles[newPlayerPos.x][newPlayerPos.y]
          .isWalkable()) {
    player.moveTo(newPlayerPos);
  }
}

void Game::update() {
  // Move enemies toward player
  Coordinate playerPos = player.getPosition();

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
  for (Tile tile : level.getCurrentRoom().tileList) {
    mvaddch(tile.getPosition().y, tile.getPosition().x, tile.getSymbol());
  }

  // Draw player... if alive.
  if (player.isAlive()) {
    Coordinate playerPos = player.getPosition();
    mvaddch(playerPos.y, playerPos.x, '@');
  }

  // Draw enemies
  for (const auto& enemy : enemies) {
    if (enemy->isAlive()) {
      Coordinate enemyPos = enemy->getPosition();
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
