#include <ncurses.h>

#include "game.h"

int main() {
  int maxX, maxY;
  // Initialize ncurses
  initscr();
  cbreak();
  noecho();
  nodelay(stdscr, TRUE);
  // include multiple special keys including keypad
  keypad(stdscr, TRUE);
  // Remove cursor from screen
  curs_set(0);
  // get terminal size
  getmaxyx(stdscr, maxY, maxX);
  Game game(maxX, maxY);
  game.run();
  return 0;
}
