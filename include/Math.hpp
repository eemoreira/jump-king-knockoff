#pragma once

#include <iostream>
#include <cmath>

struct vec2f {
    double x, y;
    vec2f(double _x = 0.0, double _y = 0.0) : x(_x), y(_y) {}

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

    vec2f operator * (double f) {
        return vec2f(x * f, y * f);
    }

    vec2f operator / (double f) {
        return vec2f(x / f, y / f);
    }
    
    vec2f& operator *= (double f) {
        x *= f;
        y *= f;
        return *this;
    }

    vec2f& operator /= (double f) {
        x /= f;
        y /= f;
        return *this;
    }

    double norm() {
        return sqrt(x * x + y * y);
    }

    double dot(vec2f oth) {
        return x * oth.x + y * oth.y;
    }

    vec2f unity() {
        return vec2f(x, y) / norm();
    }

    vec2f rotate_by(double angle) {
        // [cos -sin] [x]  = [cos * x - sin * y]
        // [sin  cos] [y]    [sin * x + cos * y]
        //
        return vec2f(std::cos(angle) * x - std::sin(angle) * y, std::sin(angle) * x + std::cos(angle) * y);
    }

    double angle_between(vec2f reflection) {
        double dt = dot(reflection);
        return acos(dt);
    }

    vec2f reflect_by(vec2f reflection_axis) {
        vec2f me = unity();
        double angle = me.angle_between(reflection_axis);
        std::cout << "angle between: ";
        print();
        std::cout << std::endl;
        reflection_axis.print();
        std::cout << std::endl << " is " << angle << std::endl;
        return me.rotate_by(angle) * norm();
    }

    void print() {
        std::cout << "(" << x << ", " << y << ")";
    }
};




