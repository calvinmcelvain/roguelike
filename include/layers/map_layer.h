#ifndef MAP_LAYER_H
#define MAP_LAYER_H

#include "level.h"
#include "render_stack.h"

class MapLayer : public RenderStack {
 public:
  /**
   * @brief Construct a new Map Layer.
   *
   * @param h Height of the layer window (in rows).
   * @param w Width of the layer window (in columns).
   * @param level The level class whose current room will be drawn each frame.
   */
  MapLayer(int h, int w, const Level& level)
      : RenderStack(h, w), level(level) {};

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

 private:
  const Level& level;
};

#endif