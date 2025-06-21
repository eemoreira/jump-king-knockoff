#pragma once

#include <iostream>

struct vec2f {
    double x, y;
    vec2f(double _x = 0.0, double _y = 0.0) : x(_x), y(_y) {}

    vec2f& operator += (vec2f& oth) {
        x += oth.x;
        y += oth.y;
        return *this;
    }

    vec2f& operator -= (vec2f& oth) {
        x -= oth.x;
        y -= oth.y;
        return *this;
    }

    vec2f operator - (vec2f& oth) {
        return vec2f(x - oth.x, y - oth.y);
    }

    vec2f operator + (vec2f& oth) {
        return vec2f(x + oth.x, y + oth.y);
    }

    void print() {
        std::cout << "(" << x << ", " << y << ")" << std::endl;
    }
};
