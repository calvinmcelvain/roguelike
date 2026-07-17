#include "render/render_stack.h"

RenderStack::RenderStack(int h, int w, int y, int x)
    : win(newwin(h, w, y, x)), height(h), width(w), originY(y), originX(x) {}

void RenderStack::reshape(int h, int w, int y, int x) {
  if (win) delwin(win);
  win = newwin(h, w, y, x);
  height = h;
  width = w;
  originY = y;
  originX = x;
}
