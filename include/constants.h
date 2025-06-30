#pragma once

#include "Math.hpp"

const int WIDTH = 1280;
const int HEIGHT = 720;
const int FLOOR_SIZE = WIDTH / 32;

const float VELOCITY = 10;

const uint64_t FPS = 60;
const uint64_t frame_delay = 1000 / FPS;
const uint64_t MILLISECONDS_TOLERANCE = 300;
const float GRAVITY = 0.0006f;
const float PLAYER_X_VELOCITY = 0.13f;
const float MAX_JUMPING_BUFFER = 1.0f;
const float BOOST = 0.05;
const float INITIAL_BOOST = 0.20;
const vec2f GROUND_LEFT_BOUND = vec2f(-WIDTH, HEIGHT);
const vec2f GROUND_RIGHT_BOUND = vec2f(2*WIDTH, HEIGHT);

enum Side { UP, DOWN, LEFT, RIGHT, NONE};
