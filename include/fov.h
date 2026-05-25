#ifndef FOV_H
#define FOV_H

#include <set>
#include <vector>

#include "vector2d.h"

class FOV {
 public:
  std::set<Vector2D> offsets;

  /**
   * @brief Construct a new FOV.
   *
   * @param offsets Set of offset positions (from origin) that defines the
   * FOV.
   *
   */
  FOV(std::set<Vector2D> offsets) : offsets(std::move(offsets)) {};

  /**
   * @brief Determine if a position is in an origin's FOV.
   *
   * Checks whether (position - origin) is one of the stored offsets.
   *
   * @param origin The position of origin with this FOV.
   * @param position The position of the target.
   * @return bool True if position is in FOV (based on origin).
   *
   */
  bool in(Vector2D origin, Vector2D position) const;

  /**
   * @brief Return all absolute positions covered by FOV from origin.
   *
   * @param origin The position of origin with this FOV.
   * @return std::vector<Vector2D>
   *
   */
  std::vector<Vector2D> absoluteFOV(Vector2D origin) const;
};

/**
 * @brief Create a filled ellipse FOV, compensating for terminal aspect ratio.
 *
 * @param radius Radius in columns (horizontal).
 * @param aspectRatio Row height / column width ratio (default 0.5 for 2:1).
 * @return FOV
 *
 */
FOV ellipseFOV(int radius, float aspectRatio = 0.5f);

#endif