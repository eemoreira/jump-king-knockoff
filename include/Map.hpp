#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <memory>
#include <iostream>
#include <algorithm>

#include "Entity.hpp"
#include "Player.hpp"
#include "Rectangle.hpp"
#include "Segment.hpp"
#include <utility>

#include "constants.h"

struct Map {
    std::vector<std::unique_ptr<Entity>> ens;
    std::vector<std::pair<std::unique_ptr<Rectangle>, uint32_t>> blocks;

    void addEntity(std::unique_ptr<Entity> en) {
        ens.emplace_back(std::move(en));
    }
    void addRectangle(std::unique_ptr<Rectangle> rec, uint32_t scene) {
        blocks.emplace_back(std::move(rec), scene);
    }

    bool inside(float me, float l, float r) {
        return me >= l && me <= r;
    }

    void move(uint32_t scene) {
        for (auto& en : ens) {
            bool col = false;

            // hit ground
            col |= en->move_bounded(WIDTH, HEIGHT) == DOWN;

            for (auto& [block, block_scene] : blocks) {
                if (scene == block_scene) {
                    // on top of a block
                    col |= en->collide_with(block.get()) == UP;
                }
            }


            if (!col) {
                en->reset_gravity();
            }
        }
    }

    Map () {}
};
