#ifndef HUD_LAYER_H
#define HUD_LAYER_H

#include "player.h"
#include "render_stack.h"

class HUDLayer : public RenderStack {
 public:
  /**
   * @brief Construct a new HUD Layer.
   *
   * @param h Height of the layer window (in rows).
   * @param w Width of the layer window in columns.
   * @param player The player object to track stats, health, position, etc.
   */
  HUDLayer(int h, int w, const Player& player)
      : RenderStack(h, w), player(player) {};

  /**
   * @brief Draw player health bar.
   *
   * Defaults to being drawn directly above player position.
   *
   * @param offsetX The offset x (column) position (relative to player) to draw
   * health bar. Positive offsets shift bar left, negative offsets shift bar
   * right. By default, 0.
   * @param offsetY The offset y (row) position (relative to player) to draw
   * health bar. Positive offsets shift bar up, negative offsets shift bar
   * down. By default, 1.
   */
  void drawPlayerHealthBar(int offsetX = 0, int offsetY = 1);

  /**
   * @brief Draw the HP indicator one row above the player's current position.
   *
   */
  void doRender() override;

 private:
  const Player& player;
};

#endif