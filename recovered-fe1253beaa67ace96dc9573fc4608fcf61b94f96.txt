#pragma once

#include <iostream>
#include <cmath>
#include <utility>

#include "Math.hpp"
#include "constants.h"

struct Segment {
    vec2f p, q;
    Side side;
    Segment(vec2f _p, vec2f _q, Side _side) : p(_p), q(_q), side(_side) {
    }

    Segment() {}

    float left_most() { return std::min(p.x, q.x); }
    float right_most() { return std::max(p.x, q.x); }
    float top_most() { return std::min(p.y, q.y); }
    float bottom_most() { return std::max(p.y, q.y); }

    std::pair<bool, vec2f> intersect(Segment oth) {
        // p + t * (q - p) = oth.p + u * (oth.q - oth.p)
        vec2f r = q - p;
        vec2f s = oth.q - oth.p;
        vec2f qp = oth.p - p;
        // p + t * r = oth.p + u * s
        if (std::abs(r.cross(s)) < -1e9) {
            return {false, {}};
        }
        float u = qp.cross(r) / r.cross(s);
        float t = qp.cross(s) / r.cross(s);
        if (t >= -0.1 && t <= 1.1 && u >= -0.1 && u <= 1.1) {
            vec2f intersection = p + r * t;
            return {true, intersection};
        }
        return {false, {}};
    }
    
    vec2f normal() {
        return (p - q).norm_perp();
    }

};





