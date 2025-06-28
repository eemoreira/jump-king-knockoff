#pragma once

#include <iostream>
#include <cmath>
#include <utility>

bool inside(float me, float l, float r) {
    return me >= l && me <= r;
}

struct vec2f {
    float x, y;
    vec2f(float _x = 0.0, float _y = 0.0) : x(_x), y(_y) {}

    vec2f& operator += (vec2f oth) {
        x += oth.x;
        y += oth.y;
        return *this;
    }

    vec2f& operator -= (vec2f oth) {
        x -= oth.x;
        y -= oth.y;
        return *this;
    }

    vec2f operator - (vec2f oth) {
        return vec2f(x - oth.x, y - oth.y);
    }

    vec2f operator + (vec2f oth) {
        return vec2f(x + oth.x, y + oth.y);
    }

    vec2f operator * (float f) {
        return vec2f(x * f, y * f);
    }

    vec2f operator / (float f) {
        return vec2f(x / f, y / f);
    }
    
    vec2f& operator *= (float f) {
        x *= f;
        y *= f;
        return *this;
    }

    vec2f& operator /= (float f) {
        x /= f;
        y /= f;
        return *this;
    }

    float norm() {
        return sqrt(x * x + y * y);
    }

    float dot(vec2f oth) {
        return x * oth.x + y * oth.y;
    }
    float cross(vec2f oth) {
        return x * oth.y - y * oth.x;
    }

    vec2f unity() {
        return vec2f(x, y) / norm();
    }

    vec2f perp() {
        // (0, -1) -> (1, 0)
        // (1, 0) -> (0, 1)
        return vec2f(-y, x);
    }

    vec2f norm_perp() {
        return perp().unity();
    }

    vec2f rotate_by(float angle) {
        // [cos -sin] [x]  = [cos * x - sin * y]
        // [sin  cos] [y]    [sin * x + cos * y]
        //
        return vec2f(std::cos(angle) * x - std::sin(angle) * y, std::sin(angle) * x + std::cos(angle) * y);
    }

    float angle_between(vec2f oth) {
        float dt = dot(oth);
        return acos(dt);
    }

    vec2f reflect_by(vec2f reflection_axis) {
        return *this - reflection_axis * 2 * dot(reflection_axis);
    }

    friend std::ostream& operator << (std::ostream& out, vec2f a) {
        return out << "(" << a.x << ", " << a.y << ")";
    }
};
