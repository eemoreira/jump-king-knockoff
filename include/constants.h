#pragma once

#include "Math.hpp"

const int WIDTH = 1280;
const int HEIGHT = 720;
const int FLOOR_SIZE = WIDTH / 32;

const double VELOCITY = 10;

const vec2f PLAYER_LEFT(-VELOCITY, 0);
const vec2f PLAYER_RIGHT(VELOCITY, 0);
const vec2f PLAYER_UP(0, -VELOCITY);
const vec2f PLAYER_DOWN(0, VELOCITY);
const uint32_t FPS = 60;
const int frame_delay = 1000 / FPS;
const int TIME_TOLERANCE = 0;
