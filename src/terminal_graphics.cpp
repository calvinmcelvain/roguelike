#include "terminal_graphics.h"
#include <iostream>

TerminalGraphics::TerminalGraphics(int width, int height)
    : width(width), height(height) {
    initBuffer();
}

void TerminalGraphics::initBuffer() {
    buffer.clear();
    buffer.resize(height, std::vector<char>(width, ' '));
}

void TerminalGraphics::clear() {
    initBuffer();
}

void TerminalGraphics::draw(int x, int y, char c) {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        buffer[y][x] = c;
    }
}

void TerminalGraphics::drawString(int x, int y, const std::string& text) {
    for (size_t i = 0; i < text.length(); i++) {
        draw(x + i, y, text[i]);
    }
}

void TerminalGraphics::render() {
    // Clear console (Windows)
    system("cls");
    
    // Draw the buffer
    for (const auto& row : buffer) {
        for (char c : row) {
            std::cout << c;
        }
        std::cout << "\n";
    }
    std::cout.flush();
}
