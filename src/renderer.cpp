#include "renderer.h"

#include <ncurses.h>

void Renderer::addLayer(int z, std::unique_ptr<RenderStack> layer) {
  layers[z] = std::move(layer);
};

void Renderer::compose() {
  erase();  // erase stdscr first.

  // iterate through the "layers", update them, render, and then layer them.
  for (auto& [z, layer] : layers) {
    if (layer->isEnabled()) {
      layer->doUpdate();
      layer->doRender();

      // overlay the ncurses::WINDOW object.
      overlay(layer->getWindow(), stdscr);
    };
  };

  // flush to terminal.
  refresh();
};
