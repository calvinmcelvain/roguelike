#include "layers/hud_layer.h"

#include <ncurses.h>

#include <algorithm>

#include "ui.h"

HUDLayer::HUDLayer(int h, int w, int margin, const Player& player,
                   const Level& level)
    : RenderStack(h, w), player(player), level(level), margin(margin) {}

void HUDLayer::drawPlayerHealthBar(int row, int col) {
  mvwprintw(win, row, col, "HP:%d/%d", player.getHealth(),
            player.getMaxHealth());
};

void HUDLayer::drawRoomID(int row, int col) {
  mvwprintw(win, row, col, "Room:%d/%d", level.getCurrentRoomID() + 1,
            level.getRoomCount());
};

void HUDLayer::doRender() {
  werase(win);  // need to erase each frame.

  // fixed HUD band above the map's top border, with a blank gap row
  // separating the HUD text from the border itself.
  UI geom = computeUI(height, width);
  int bandRow = std::max(0, geom.originY - margin);

  this->drawRoomID(bandRow, geom.originX);
  this->drawPlayerHealthBar(bandRow + 1, geom.originX);
};
