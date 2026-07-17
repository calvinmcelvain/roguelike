#include "render/layers/entity_layer.h"

#include <ncurses.h>

#include <memory>

#include "render/ui.h"

EntityLayer::EntityLayer(int h, int w, int y, int x, const Player& player,
                         const std::vector<std::unique_ptr<Enemy>>& enemies)
    : RenderStack(h, w, y, x), player(player), enemies(enemies) {}

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

void EntityLayer::onResize(int termHeight, int termWidth) {
  UI g = computeUI(termHeight, termWidth);
  reshape(g.winHeight, g.winWidth, g.originY, g.originX);
};
