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
    auto elapsed =
        std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (elapsed < frame_duration) {
      std::this_thread::sleep_for(frame_duration - elapsed);
    }

    // for debug window.
    std::chrono::duration<double, std::milli> totalFrame =
        std::chrono::high_resolution_clock::now() - start;

    currentFps = totalFrame.count() > 0.0 ? 1000.0 / totalFrame.count() : 0.0;
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

void Game::render() { renderer.compose(); };

void Game::spawnEnemies() {
  enemies.push_back(std::make_unique<Enemy>(10, 10, 'G'));
  enemies.push_back(std::make_unique<Enemy>(20, 15, 'O'));
}
