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

    vec2f operator * (double f) {
        return vec2f(x * f, y * f);
    }
    
    vec2f& operator *= (double f) {
        x *= f;
        y *= f;
        return *this;
    }

    void print() {
        std::cout << "(" << x << ", " << y << ")" << std::endl;
    }
};
