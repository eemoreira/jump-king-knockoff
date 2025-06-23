#pragma once

#include <iostream>
#include <cmath>
#include <utility>

bool inside(double me, double l, double r) {
    return me >= l && me <= r;
}

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
    double cross(vec2f oth) {
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

    vec2f rotate_by(double angle) {
        // [cos -sin] [x]  = [cos * x - sin * y]
        // [sin  cos] [y]    [sin * x + cos * y]
        //
        return vec2f(std::cos(angle) * x - std::sin(angle) * y, std::sin(angle) * x + std::cos(angle) * y);
    }

    double angle_between(vec2f oth) {
        double dt = dot(oth);
        return acos(dt);
    }

    vec2f reflect_by(vec2f reflection_axis) {
        return *this - reflection_axis * 2 * dot(reflection_axis);
    }

    void print() {
        std::cout << "(" << x << ", " << y << ")";
    }
};

struct Segment {
    vec2f p, q;
    Segment(vec2f _p, vec2f _q) : p(_p), q(_q) {
    }

    Segment() {}

    std::pair<bool, vec2f> intersect(Segment oth) {
        // p + t * (q - p) = oth.p + u * (oth.q - oth.p)
        vec2f r = q - p;
        vec2f s = oth.q - oth.p;
        vec2f qp = oth.p - p;
        // p + t * r = oth.p + u * s
        if (std::abs(r.cross(s)) < -1e9) {
            return {false, {}};
        }
        double u = qp.cross(r) / r.cross(s);
        double t = qp.cross(s) / r.cross(s);
        if (t >= 0.0 && t <= 1.0 && u >= 0.0 && u <= 1.0) {
            vec2f intersection = p + r * t;
            return {true, intersection};
        }
        return {false, {}};
    }
    
    vec2f normal() {
        return (p - q).norm_perp();
    }

};




