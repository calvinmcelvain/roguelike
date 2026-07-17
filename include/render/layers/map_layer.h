#ifndef MAP_LAYER_H
#define MAP_LAYER_H

#include "world/level.h"
#include "render/render_stack.h"

class MapLayer : public RenderStack {
 public:
  /**
   * @brief Construct a new Map Layer.
   *
   * @param h Height of the layer window (in rows).
   * @param w Width of the layer window (in columns).
   * @param y Row of the window's top-left corner in the terminal.
   * @param x Column of the window's top-left corner in the terminal.
   * @param level The level class whose current room will be drawn each frame.
   */
  MapLayer(int h, int w, int y, int x, const Level& level);

  /**
   * @brief Draw all room tiles into the map layer window.
   *
   */
  void drawMap();

  /**
   * @brief Render map layer window.
   *
   */
  void doRender() override;

  /**
   * @brief Recompute the centered, terminal-clamped map window geometry.
   *
   * @param termHeight New terminal height (rows).
   * @param termWidth New terminal width (columns).
   */
  void onResize(int termHeight, int termWidth) override;

 private:
  const Level& level;
};

#endif