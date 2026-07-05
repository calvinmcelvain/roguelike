#ifndef DEBUG_LAYER_H
#define DEBUG_LAYER_H

#include "coordinate.h"
#include "render_stack.h"

class DebugLayer : public RenderStack {
 public:
  /**
   * @brief Construct a new Debug Layer.
   *
   * @param h Height of the layer window (in rows).
   * @param w Width of the layer window (in columns).
   * @param fps The frames-per-second of game.
   * @param frameTimeMs The milliseconds between frames after rendering.
   * @param playerPos The current position of the player.
   */
  DebugLayer(int h, int w, const int& fps, double& frameTimeMs,
             const Coordinate& playerPos)
      : RenderStack(h, w),
        fps(fps),
        frameTimeMs(frameTimeMs),
        playerPos(playerPos) {};

  /**
   * @brief Draw frame timing and player position at the bottom row.
   *
   */
  void doRender() override;

 private:
  const int& fps;
  double& frameTimeMs;
  const Coordinate& playerPos;
};

#endif