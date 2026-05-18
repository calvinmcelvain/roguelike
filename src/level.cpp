#include "level.h"

Level::Level(int width, int height)
    : width(width), height(height) {
    generate();
}

void Level::generate() {
    tiles.resize(height, std::vector<char>(width, ' '));
    
    // Draw borders
    for (int x = 0; x < width; x++) {
        tiles[0][x] = '#';
        tiles[height - 1][x] = '#';
    }
    
    for (int y = 0; y < height; y++) {
        tiles[y][0] = '#';
        tiles[y][width - 1] = '#';
    }
}

bool Level::isWalkable(Vector2D pos) const {
    if (pos.x < 0 || pos.x >= width || pos.y < 0 || pos.y >= height)
        return false;
    
    char tile = tiles[pos.y][pos.x];
    return tile != '#';
}

char Level::getTile(Vector2D pos) const {
    if (pos.x < 0 || pos.x >= width || pos.y < 0 || pos.y >= height)
        return ' ';
    return tiles[pos.y][pos.x];
}
