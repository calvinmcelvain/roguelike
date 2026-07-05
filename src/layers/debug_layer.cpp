#include "layers/debug_layer.h"

void DebugLayer::doRender() {
  werase(win);  // need to erase each frame.

  mvwprintw(win, height - 1, 0, "FPS:%d.%d (%d,%d)", fps, frameTimeMs,
            playerPos.x, playerPos.y);
};
