#include "colors.h"

#include <ncurses.h>

namespace {

// Extended 16-colour palette index 8 is "bright black" — dark grey on
// essentially every modern terminal. Kept as a named constant so the
// intent is obvious at the pair-registration sites below.
constexpr short kGreyDark = 8;

// Small helper so pair registration reads naturally with the enum-class
// values rather than static_cast noise at every call site.
void registerPair(ColorPair id, short fg, short bg) {
  init_pair(static_cast<short>(id), fg, bg);
}

}  // namespace

void initColors() {
  if (!has_colors()) return;

  start_color();

  // Solid dark-grey block: fg == bg so the glyph itself is invisible and
  // only the cell background shows through. Any non-blank character in
  // MapLayer paired with this attribute renders as an opaque grey tile.
  registerPair(ColorPair::FogUnexplored, kGreyDark, kGreyDark);

  // Explored-but-not-visible: same grey background as FogUnexplored so
  // the "shadow" of previously seen area stays visible after the FoV
  // moves off it. Only the fg differs — MapLayer draws the tile's normal
  // glyph in light grey (COLOR_WHITE) on top of the grey shade, so walls
  // and floors remain readable while the area is clearly out-of-sight.
  registerPair(ColorPair::FogExplored, COLOR_WHITE, kGreyDark);

  // ColorPair::EnemyDefault and ColorPair::DoorDefault are reserved but
  // intentionally not registered yet — future work will choose their
  // fg/bg and add the corresponding registerPair() calls here.
}
