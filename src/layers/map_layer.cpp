#include "layers/map_layer.h"

#include <ncurses.h>

#include "room.h"

MapLayer::MapLayer(int h, int w, const Level& level)
    : RenderStack(h, w), level(level) {}

void MapLayer::drawMap() {
  const Room& room = level.getCurrentRoom();

  for (int x = 0; x < Room::WIDTH; ++x) {
    for (int y = 0; y < Room::HEIGHT; ++y) {
      // get tile reference & print it.
      const Tile& tile = room.tiles[x][y];

      // 3-state fog of war:
      //   visible  -> normal render
      //   explored -> dimmed render (terrain only; entities are handled
      //               separately in EntityLayer)
      //   unseen   -> skip so the cell stays blank/black
      if (room.isVisible(x, y)) {
        mvwaddch(win, tile.getPosition().y, tile.getPosition().x,
                 tile.getSymbol());
      } else if (room.isExplored(x, y)) {
        mvwaddch(win, tile.getPosition().y, tile.getPosition().x,
                 tile.getSymbol() | A_DIM);
      }
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
