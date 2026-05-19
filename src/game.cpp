#include "game.h"

#include <conio.h>

#include <iostream>

#include "enemy.h"

Game::Game(int width, int height)
    : screenWidth(width),
      screenHeight(height),
      player(width / 2, height / 2),
      level(width, height),
      graphics(width, height),
      isRunning(true) {
  spawnEnemies();
}

void Game::run() {
  std::cout
      << "Roguelike Game Started! Use arrow keys to move. Press Q to quit.\n";
  std::cout << "Press any key to begin...\n";
  _getch();

  while (isRunning) {
    handleInput();
    update();
    render();
  }

  std::cout << "Game Over!\n";
}

void Game::handleInput() {
  if (_kbhit()) {
    int ch = _getch();

    switch (ch) {
      case 'q':
      case 'Q':
        isRunning = false;
        break;
      case 224:  // Extended key
      {
        int arrowKey = _getch();
        Vector2D newPos = player.getPosition();

        if (arrowKey == 72)
          newPos.y--;  // Up
        else if (arrowKey == 80)
          newPos.y++;  // Down
        else if (arrowKey == 75)
          newPos.x--;  // Left
        else if (arrowKey == 77)
          newPos.x++;  // Right

        if (level.isWalkable(newPos)) {
          if (arrowKey == 72)
            player.moveUp();  // Up
          else if (arrowKey == 80)
            player.moveDown();  // Down
          else if (arrowKey == 75)
            player.moveLeft();  // Left
          else if (arrowKey == 77)
            player.moveRight();  // Right
        }
        break;
      }
    }
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
  graphics.clear();

  // Draw level
  for (int y = 0; y < level.getHeight(); y++) {
    for (int x = 0; x < level.getWidth(); x++) {
      graphics.draw(x, y, level.getTile(Vector2D(x, y)));
    }
  }

  // Draw player
  Vector2D playerPos = player.getPosition();
  graphics.draw(playerPos.x, playerPos.y, '@');

  // Draw enemies
  for (const auto& enemy : enemies) {
    if (enemy->isAlive()) {
      Vector2D enemyPos = enemy->getPosition();
      graphics.draw(enemyPos.x, enemyPos.y, enemy->getSymbol());
    }
  }

  // Draw UI
  graphics.drawString(1, screenHeight - 1,
                      "HP: " + std::to_string(player.getHealth()) + "/" +
                          std::to_string(player.getMaxHealth()));

  graphics.render();
}

void Game::spawnEnemies() {
  enemies.push_back(std::make_unique<Enemy>(10, 10, 'G'));
  enemies.push_back(std::make_unique<Enemy>(20, 15, 'O'));
}
