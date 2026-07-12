#include "layers/debug_layer.h"

DebugLayer::DebugLayer(int h, int w, const double& currentFps,
                       const Player& player)
    : RenderStack(h, w), currentFps(currentFps), player(player) {}

void DebugLayer::doRender() {
  werase(win);  // need to erase each frame.

  Coordinate pos = player.getPosition();
  mvwprintw(win, height - 1, 0, "FPS:%.2f|Position:(%d,%d)", currentFps, pos.x,
            pos.y);
};
