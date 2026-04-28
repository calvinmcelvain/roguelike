#ifndef VECTOR2D_H
#define VECTOR2D_H

struct Vector2D {
    int x, y;
    
    Vector2D(int x = 0, int y = 0) : x(x), y(y) {}
    
    Vector2D operator+(const Vector2D& other) const {
        return Vector2D(x + other.x, y + other.y);
    }
    
    Vector2D operator-(const Vector2D& other) const {
        return Vector2D(x - other.x, y - other.y);
    }
    
    bool operator==(const Vector2D& other) const {
        return x == other.x && y == other.y;
    }
};

#endif
