#include <ncurses.h>

#include <cstdlib>
#include <ctime>

#include "game.h"

int main() {
  // Seed the random number generator once at startup so room shapes, door
  // layouts, and enemy positions differ on every run.
  srand(static_cast<unsigned int>(time(nullptr)));

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
