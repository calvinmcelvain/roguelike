#ifndef TERMINAL_GRAPHICS_H
#define TERMINAL_GRAPHICS_H

#include <string>
#include <vector>

class TerminalGraphics {
 public:
  TerminalGraphics(int width, int height);

  // Clear screen
  void clear();

  // Draw a character at position
  void draw(int x, int y, char c);

  // Draw a string at position
  void drawString(int x, int y, const std::string& text);

  // Render all drawn content
  void render();

  // Get dimensions
  int getWidth() const { return width; }
  int getHeight() const { return height; }

 private:
  int width, height;
  std::vector<std::vector<char>> buffer;

  void initBuffer();
};

#endif
