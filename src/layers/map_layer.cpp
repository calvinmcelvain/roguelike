#include "layers/map_layer.h"

#include <ncurses.h>

#include "room.h"
#include "ui.h"

MapLayer::MapLayer(int h, int w, int y, int x, const Level& level)
    : RenderStack(h, w, y, x), level(level) {}

void MapLayer::drawMap() {
  const Room& room = level.getCurrentRoom();

  for (int x = 0; x < Room::WIDTH; ++x) {
    for (int y = 0; y < Room::HEIGHT; ++y) {
      // get tile reference & print it.
      const Tile& tile = room.tiles[x][y];

      mvwaddch(win, tile.getPosition().y, tile.getPosition().x,
               tile.getSymbol());
    };
  };
};

void MapLayer::doRender() {
  werase(win);  // need to erase each frame.

  // boarder around map.
  box(win, 0, 0);

  // draw map.
  this->drawMap();
};

void MapLayer::onResize(int termHeight, int termWidth) {
  UI g = computeUI(termHeight, termWidth);
  reshape(g.winHeight, g.winWidth, g.originY, g.originX);
};
