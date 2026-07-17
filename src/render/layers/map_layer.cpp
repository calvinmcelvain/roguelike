#include "render/layers/map_layer.h"

#include <ncurses.h>

#include "world/room.h"
#include "render/ui.h"
#include "core/colors.h"

MapLayer::MapLayer(int h, int w, int y, int x, const Level& level)
    : RenderStack(h, w, y, x), level(level) {}

void MapLayer::drawMap() {
  const Room& room = level.getCurrentRoom();

  for (int x = 0; x < Room::WIDTH; ++x) {
    for (int y = 0; y < Room::HEIGHT; ++y) {
      // get tile reference & print it.
      const Tile& tile = room.tiles[x][y];
      const int tx = tile.getPosition().x;
      const int ty = tile.getPosition().y;

      // 3-state fog of war:
      //   visible   -> normal render (terminal default colours).
      //   explored  -> light grey glyph on grey background for non-blank
      //                tile symbols (walls, doors). Blank symbols (floor)
      //                are substituted with a solid grey block because
      //                ncurses overlay() drops blank cells — writing ' '
      //                with a coloured bg would still be treated as
      //                transparent and let the black stdscr show through.
      //                Result: the whole explored area reads as a uniform
      //                grey shade with walls/doors picked out on top.
      //   unseen    -> solid dark grey block so the room shape stays
      //                hidden until first sighting.
      //
      // Hook: door tiles could branch here on tile.getType() == Door and
      // OR in colorAttr(ColorPair::DoorDefault) once the pair is defined.
      if (room.isVisible(x, y)) {
        mvwaddch(win, ty, tx, tile.getSymbol());
      } else if (room.isExplored(x, y)) {
        const char sym = tile.getSymbol();
        if (sym == ' ') {
          // Blank glyph -> solid grey (fg == bg) so the shading persists.
          mvwaddch(win, ty, tx, '.' | colorAttr(ColorPair::FogUnexplored));
        } else {
          mvwaddch(win, ty, tx, sym | colorAttr(ColorPair::FogExplored));
        }
      } else {
        // Fog block: ncurses overlay() drops blanks, so we must draw a
        // non-blank glyph. Because the pair has fg == bg, whatever glyph
        // we pick is invisible against its own background and only the
        // solid grey cell shows through. '.' is arbitrary.
        mvwaddch(win, ty, tx, '.' | colorAttr(ColorPair::FogUnexplored));
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

void MapLayer::onResize(int termHeight, int termWidth) {
  UI g = computeUI(termHeight, termWidth);
  reshape(g.winHeight, g.winWidth, g.originY, g.originX);
};
