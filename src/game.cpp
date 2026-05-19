#include "game.h"

#include <ncurses.h>

#include <cstdlib>
#include <iostream>
#include <chrono>
#include <thread>

#include "enemy.h"

Game::Game(int width, int height)
    : screenWidth(width),
      screenHeight(height),
      player(width / 2, height / 2),
      level(width, height),
      isRunning(true) {
  spawnEnemies();
}

void Game::run() {
  printw("Roguelike Game Started! Use arrow keys to move. Press Q to quit.\n");
  printw("Press any key to begin...\n");
  box(stdscr, 0, 0);
  refresh();
  const int FPS = 60;
  const int FRAME_TIME = 1000 / FPS;

  while (isRunning) {
    auto start = std::chrono::high_resolution_clock::now();
    handleInput();
    update();
    render();
    // -------- FPS control --------
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed =
      std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    if (elapsed < FRAME_TIME) {
      std::this_thread::sleep_for(
        std::chrono::milliseconds(FRAME_TIME - elapsed));
    }
  }

  endwin();
  std::cout << "Game Over!\n";
}

void Game::handleInput() {
  int ch = getch();  
  Vector2D newPos = player.getPosition();

  switch (ch) {
    case KEY_UP:  // Up
      newPos.y--;
      break;
    case KEY_DOWN:  // Down
      newPos.y++;
      break;
    case KEY_LEFT:  // Left
      newPos.x--;
      break;
    case KEY_RIGHT:  // Right
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

    player.moveTo(newPos);
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

  // Draw player
  Vector2D playerPos = player.getPosition();
  mvaddch(playerPos.y, playerPos.x, '@');

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
