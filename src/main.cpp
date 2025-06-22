#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <array>
#include <vector>
#include <cassert>

#include "RenderWindow.hpp"
#include "Entity.hpp" 
#include "Player.hpp"
#include "Map.hpp"
#include "KeyHandler.hpp"
#include "Rectangle.hpp"
#include "constants.h"

int main(int argv, char* args[]) {
	if (SDL_Init(SDL_INIT_VIDEO) > 0) {
		std::cout << "ERROR ON SDL_INIT: " << SDL_GetError() << std::endl; 
		return 1;
	}
	if (!IMG_Init(IMG_INIT_PNG)) {
		std::cout << "ERROR ON IMG_INIT: " << IMG_GetError() << std::endl; 
		return 1;
	}

    RenderWindow win("jump king - hehe", WIDTH, HEIGHT);

    SDL_Texture* grass = win.loadTexture("res/gfx/ground_grass_1.png");
    SDL_Texture* block = win.loadTexture("res/gfx/brackeys_platformer_assets/sprites/block.png");
//    SDL_Texture* plat = win.loadTexture("res/gfx/brackeys_platformer_assets/sprites/platforms.png");
    SDL_Texture* static_knight = win.loadTexture("res/gfx/brackeys_platformer_assets/sprites/static_knight.png");

//    std::vector<std::unique_ptr<Entity>> grass_blocks;
//
//    SDL_Rect grass_rect;
//    grass_rect.x = grass_rect.y = 0;
//    grass_rect.w = grass_rect.h = 32;

//  for (int i = 0; i < FLOOR_SIZE; i++) {
//      grass_blocks.emplace_back(
//              std::make_unique<Entity>(vec2f(32 * i, HEIGHT - 32), 
//                                       vec2f(0, 0),
//                                       grass, 
//                                       grass_rect, 
//                                       1)
//      );
//  }

//    std::vector<std::unique_ptr<Entity>> platforms;
//
//    SDL_Rect plat_rect;
//    plat_rect.x = plat_rect.y = 0;
//    plat_rect.w = 16;
//    plat_rect.h = 8;

//    const int NUM_PLATFORMS = 5;
//    for (int i = 1; i <= NUM_PLATFORMS; i++) {
//        platforms.emplace_back(std::make_unique<Entity>(
//                    vec2f(0, HEIGHT - 100 * i), 
//                    vec2f(0.1, 0),
//                    plat, 
//                    plat_rect, 
//                    3)
//        );
//        platforms.emplace_back(std::make_unique<Entity>(
//                    vec2f(WIDTH - 16 * 3, HEIGHT - 100 * i), 
//                    vec2f(-0.1, 0),
//                    plat, 
//                    plat_rect, 
//                    3)
//        );
//    }
//

    SDL_Rect player_rect;
    player_rect.x = player_rect.y = 0;
    player_rect.w = 13;
    player_rect.h = 19;

    std::unique_ptr<Player> player_ptr = std::make_unique<Player>(
            vec2f(0, HEIGHT - 4*player_rect.h),
            static_knight, 
            player_rect, 
            4
    );

    Player* player = player_ptr.get();

    Map mapa;
    mapa.addEntity(std::move(player_ptr));
    for (int i = 0; i < 2; i++) {
        auto rec = std::make_unique<Rectangle>(
                block,
                vec2f(150, i * 200),
                200,
                300
        );
        mapa.addRectangle(std::move(rec));
    }

    KeyHandler key_handler;
    bool running = true;
    SDL_Event event;

    uint64_t currentFrame = 0;
    while (running) {

        uint64_t first_frame = SDL_GetTicks();
        currentFrame += 1;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            } else if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
                key_handler.update_key(event.key);
            }
        }


        bool R_PRESSED = key_handler.is_pressed(SDL_SCANCODE_RIGHT, SDL_GetTicks(), TIME_TOLERANCE); 
        bool L_PRESSED = key_handler.is_pressed(SDL_SCANCODE_LEFT, SDL_GetTicks(), TIME_TOLERANCE); 

        bool R_RELEASED = key_handler.is_released(SDL_SCANCODE_RIGHT, SDL_GetTicks(), TIME_TOLERANCE); 
        bool L_RELEASED = key_handler.is_released(SDL_SCANCODE_LEFT, SDL_GetTicks(), TIME_TOLERANCE); 

        bool SPACE_PRESSED = key_handler.is_pressed(SDL_SCANCODE_SPACE, SDL_GetTicks(), TIME_TOLERANCE); 
        bool SPACE_RELEASED = key_handler.is_released(SDL_SCANCODE_SPACE, SDL_GetTicks(), TIME_TOLERANCE); 

        if (L_PRESSED && R_PRESSED) {
            player->set_vel(vec2f(0, (player->vel).y));
        } else if (L_PRESSED) {
            //std::cout << "LEFT IS PRESSED" << std::endl;
            player->set_vel(vec2f(-0.15, (player->vel).y));
        } else if (R_PRESSED) {
            //std::cout << "RIGHT IS PRESSED" << std::endl;
            player->set_vel(vec2f(0.15, (player->vel).y));
        } else if (L_RELEASED ) {
            //std::cout << "LEFT IS RELEASED" << std::endl;
            player->set_vel(vec2f(0, (player->vel).y));
        } else if (R_RELEASED) {
            //std::cout << "RIGHT IS RELEASED" << std::endl;
            player->set_vel(vec2f(0, (player->vel).y));
        }

        player->set_face();

        if (SPACE_PRESSED) {
            std::cout << "SPACE IS PRESSED" << std::endl;
            player->boost(0.1);
        } else if (SPACE_RELEASED) {
            //std::cout << "SPACE IS RELEASED" << std::endl;
            player->jump();
        }

        uint64_t frame_time = SDL_GetTicks() - first_frame;

        if (frame_time > frame_delay) {
            SDL_Delay(frame_time - frame_delay);
        }

        win.clear();
        mapa.move();
        win.render(mapa);
        win.display();
    }


    SDL_Quit();
	return 0;
}
