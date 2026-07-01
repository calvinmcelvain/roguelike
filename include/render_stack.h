#ifndef RENDER_STACK_H
#define RENDER_STACK_H

#include <ncurses.h>

class RenderStack {
 public:
  /**
   * @brief Construct a new Render Stack object.
   *
   * @param h Height of the layer window (in rows).
   * @param w Width of the layer window (in columns).
   */
  RenderStack::RenderStack(int h, int w)
      : win(newwin(h, w, 0, 0)), height(h), width(w) {};

  // need to make sure the ncurses::WINDOW is deleted if object is.
  virtual ~RenderStack() {
    if (win) delwin(win);
  };

  // doing this to enforce no copies. each RenderStack object should be unique.
  RenderStack(const RenderStack&) = delete;
  RenderStack& operator=(const RenderStack&) = delete;
  RenderStack(RenderStack&&) = delete;
  RenderStack& operator=(RenderStack&&) = delete;

  /**
   * @brief State update hook. Default is a no-op.
   *
   * Called by Renderer before doRender() each frame. Override to update
   * any derived-class state that must be refreshed before drawing.
   */
  virtual void doUpdate() {};

  /**
   * @brief Draw this layer's content on the WINDOW.
   *
   */
  virtual void doRender() = 0;

  /**
   * @brief Enable or disable this layer. Disabled layers are skipped entirely
   * by Renderer::compose().
   *
   * @param e True to enable, false to disable.
   */
  void setEnabled(bool e) { enabled = e; };

  /**
   * @brief Check whether this layer is currently enabled.
   *
   * @return bool
   */
  bool isEnabled() const { return enabled; };

  /**
   * @brief Get the WINDOW.
   *
   * @return WINDOW*
   */
  WINDOW* getWindow() const { return win; };

 protected:
  WINDOW* win;
  const int height;
  const int width;

 private:
  bool enabled = true;
};

#endif
