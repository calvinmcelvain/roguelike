#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "level.h"
#include "terminal_graphics.h"
#include <vector>
#include <memory>

class Enemy;

class Game {
public:
    Game(int width = 80, int height = 24);
    
    // Main game loop
    void run();
    
private:
    int screenWidth, screenHeight;
    Player player;
    Level level;
    TerminalGraphics graphics;
    std::vector<std::unique_ptr<Enemy>> enemies;
    
    bool isRunning;
    
    // Game phases
    void handleInput();
    void update();
    void render();
    void spawnEnemies();
    
    // Utility
    void setupTerminal();
    void restoreTerminal();
};

#endif
