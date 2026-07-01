#include "layers/hud_layer.h"

#include <ncurses.h>

void HUDLayer::drawPlayerHealthBar(int offsetX = 0, int offsetY = 1) {
  // only draw if the position isn't ontop of player.
  // TODO: add a warning log if this is ever true?
  if (offsetX != 0 or offsetY != 0) {
    // get the player's current position.
    Coordinate pos = player.getPosition();

    // get the absolute position to draw the health bar.
    int barX = pos.x - offsetX;
    int barY = pos.y - offsetY;

    mvwprintw(win, barY, barX, "HP:%d/%d", player.getHealth(),
              player.getMaxHealth());
  };
};

void HUDLayer::doRender() {
  werase(win);  // need to erase each frame.

  // draw player health bar.
  this->drawPlayerHealthBar();
};
