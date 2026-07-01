#include "layers/debug_layer.h"

void DebugLayer::doRender() {
  werase(win);  // need to erase each frame.

  Coordinate pos = player.getPosition();
  mvwprintw(win, height - 1, 0, "FPS:%.2f|Position:(%d,%d)", currentFps, pos.x,
            pos.y);
};
