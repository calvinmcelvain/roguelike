#ifndef RENDER_STACK_H
#define RENDER_STACK_H

#include <ncurses.h>
#include <panel.h>

#include <vector>

class RenderStack {
 public:
  /**
   * @brief Construct a new Render Stack object.
   *
   * @param panels Panel objects to render groupwise.
   */
  RenderStack(std::vector<PANEL*> panels) : panels(panels) {};

  /**
   * @brief Updates panel positions & data.
   *
   */
  void doUpdate();

  /**
   * @brief Renders stack on terminal.
   *
   */
  void doRender();

 private:
  std::vector<PANEL*> panels;
};

#endif