#include "render_stack.h"

RenderStack::RenderStack(int h, int w)
    : win(newwin(h, w, 0, 0)), height(h), width(w) {}
