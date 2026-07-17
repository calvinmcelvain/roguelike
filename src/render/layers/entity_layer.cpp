#include "render/layers/entity_layer.h"

#include <ncurses.h>

#include <memory>

#include "render/ui.h"

EntityLayer::EntityLayer(int h, int w, int y, int x, const Level& level, const Player& player,
                         const std::vector<std::unique_ptr<Enemy>>& enemies)
    : RenderStack(h, w, y, x), level(level), player(player), enemies(enemies) {}

void EntityLayer::drawEnemies() {
  const Room& room = level.getCurrentRoom();

  // iterate through vector of enemies.
  for (const auto& enemy : enemies) {
    // if alive AND inside the player's current FoV, draw symbol.
    // Dynamic content (enemies) is never shown outside the FoV, even if
    // the tile they stand on is "explored".
    if (enemy->isAlive()) {
      Coordinate pos = enemy->getPosition();

      if (room.isVisible(pos.x, pos.y)) {
        // Hook: OR in colorAttr(ColorPair::EnemyDefault) — or a
        // per-enemy-type pair — once enemy colouring is designed.
        mvwaddch(win, pos.y, pos.x, enemy->getSymbol());
      }
    };
    // TODO: if enemy dead, destroy the object & update the vector? lil
    // optimization??
  };
};

void EntityLayer::drawPlayer() {
  // if alive, draw symbol. Player is always at their own FoV origin so
  // no visibility check is needed here.
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
