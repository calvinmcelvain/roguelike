
#include "fov.h"

#include <set>
#include <vector>

bool FOV::in(Vector2D origin, Vector2D position) const {
  Vector2D offset = origin - position;
  return offsets.count(offset) > 0;
};

std::vector<Vector2D> FOV::absoluteFOV(Vector2D origin) const {
  // initialize a vector of positions w/ size of number of offsets.
  std::vector<Vector2D> positions;
  positions.reserve(offsets.size());

  // iterate through & get the absolute position based on origin pos.
  for (const Vector2D& offset : offsets) {
    positions.push_back(origin + offset);
  };

  return positions;
};

FOV ellipseFOV(int rx, int ry) {
  // need to get all offsets to create an FOV.
  std::set<Vector2D> offsets;

  // iterate through -y --> y.
  for (int dy = -ry; dy <= ry; ++dy) {
    // find max x via ellipse eq. (w/ origin 0):
    //    1 = (dx / rx)^2 + (dy / ry)^2
    //    dx = rx * sqrt(1 - (dy / ry)^2)
    // could've used std::ceil here, but rounding down is fine w/ me.
    float y_norm = dy / ry;
    int dx_max = static_cast<int>(rx * std::sqrt(1.0f - y_norm * y_norm));

    // iterate through -dx --> dx.
    for (int dx = -dx_max; dx <= dx_max; ++dx) {
      offsets.insert({dx, dy});
    };
  }

  // cooked.
  return FOV(offsets);
}