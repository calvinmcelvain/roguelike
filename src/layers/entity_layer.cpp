#include "layers/entity_layer.h"

#include <ncurses.h>

void EntityLayer::drawEnemies() {
  // iterate through vector of enemies.
  for (const auto& enemy : enemies) {
    // if alive, draw symbol.
    if (enemy->isAlive()) {
      Coordinate pos = enemy->getPosition();

      mvwaddch(win, pos.y, pos.x, enemy->getSymbol());
    };
    // TODO: if enemy dead, destroy the object & update the vector? lil
    // optimization??
  };
};

void EntityLayer::drawPlayer() {
  // if alive, draw symbol.
  if (player.isAlive()) {
    Coordinate pos = player.getPosition();

    mvwaddch(win, pos.y, pos.x, player.getSymbol());
  };
};

void EntityLayer::doRender() {
  werase(win);  // need to erase each frame.

  // render enemies first, then player (top of render).
  this->drawEnemies();
  this->drawPlayer();
};
