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
    SDL_Texture* plat = win.loadTexture("res/gfx/brackeys_platformer_assets/sprites/platforms.png");
    SDL_Texture* static_knight = win.loadTexture("res/gfx/brackeys_platformer_assets/sprites/static_knight.png");

    std::vector<std::unique_ptr<Entity>> grass_blocks;

    SDL_Rect grass_rect;
    grass_rect.x = grass_rect.y = 0;
    grass_rect.w = grass_rect.h = 32;

  //  for (int i = 0; i < FLOOR_SIZE; i++) {
  //      grass_blocks.emplace_back(
  //              std::make_unique<Entity>(vec2f(32 * i, HEIGHT - 32), 
  //                                       vec2f(0, 0),
  //                                       grass, 
  //                                       grass_rect, 
  //                                       1)
  //      );
  //  }

    std::vector<std::unique_ptr<Entity>> platforms;

    SDL_Rect plat_rect;
    plat_rect.x = plat_rect.y = 0;
    plat_rect.w = 16;
    plat_rect.h = 8;

    const int NUM_PLATFORMS = 5;
    for (int i = 1; i <= NUM_PLATFORMS; i++) {
        platforms.emplace_back(std::make_unique<Entity>(
                    vec2f(0, HEIGHT - 100 * i), 
                    vec2f(0.1, 0),
                    plat, 
                    plat_rect, 
                    3)
        );
        platforms.emplace_back(std::make_unique<Entity>(
                    vec2f(WIDTH - 16 * 3, HEIGHT - 100 * i), 
                    vec2f(-0.1, 0),
                    plat, 
                    plat_rect, 
                    3)
        );
    }

    SDL_Rect player_rect;
    player_rect.x = player_rect.y = 0;
    player_rect.w = 13;
    player_rect.h = 19;
    std::unique_ptr<Player> player_ptr = std::make_unique<Player>(
            vec2f(0, HEIGHT - 32 - 4*player_rect.h),
            static_knight, 
            player_rect, 
            4
    );

    Player* player = player_ptr.get();

    Map mapa;
    mapa.add(std::move(player_ptr));

    for (std::unique_ptr<Entity>& en : platforms) {
        mapa.add(std::move(en));
    }

   // for (std::unique_ptr<Entity>& en : grass_blocks) {
   //     mapa.add(std::move(en));
   // }

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

        uint64_t frame_time = SDL_GetTicks() - first_frame;

        if (frame_time > frame_delay) {
            SDL_Delay(frame_time - frame_delay);
        }

        auto key_events = key_handler.get_key_events(SDL_GetTicks(), TIME_TOLERANCE);

        for (const SDL_KeyboardEvent& e : key_events) {
            if (key_handler.is_pressed(e.keysym.scancode)) {
                switch (e.keysym.scancode) {
                    case SDL_SCANCODE_RIGHT:
                        player->set_vel(vec2f(0.15, 0));
                        break;
                    case SDL_SCANCODE_LEFT:
                        player->set_vel(vec2f(-0.15, 0));
                        break;
                    default:
                        break;
                }
            }
            if (key_handler.is_released(e.keysym.scancode)) {
                switch (e.keysym.scancode) {
                    case SDL_SCANCODE_RIGHT:
                        player->set_vel(vec2f(0, 0));
                        break;
                    case SDL_SCANCODE_LEFT:
                        player->set_vel(vec2f(0, 0));
                        break;
                    default:
                        break;
                }
            }
        }

        win.clear();
        mapa.move();
        win.render(mapa);
        win.display();
    }


    SDL_Quit();
	return 0;
}
