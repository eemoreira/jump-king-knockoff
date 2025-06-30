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

    SDL_Texture* knight_facing_right = win.loadTexture("res/gfx/brackeys_platformer_assets/sprites/knight_facing_right.png");
    SDL_Texture* knight_facing_left = win.loadTexture("res/gfx/brackeys_platformer_assets/sprites/knight_facing_left.png");
    SDL_Texture* crouched_knight_facing_right = win.loadTexture("res/gfx/brackeys_platformer_assets/sprites/crouched_knight_facing_right.png");
    SDL_Texture* crouched_knight_facing_left = win.loadTexture("res/gfx/brackeys_platformer_assets/sprites/crouched_knight_facing_left.png");

    SDL_Rect player_rect;
    player_rect.x = player_rect.y = 0;
    player_rect.w = 13;
    player_rect.h = 19;

    std::unique_ptr<Player> player_ptr = std::make_unique<Player>(
            vec2f(100, HEIGHT - 4*player_rect.h),
            std::vector<SDL_Texture*> {knight_facing_right, knight_facing_left, crouched_knight_facing_right, crouched_knight_facing_left}, 
            player_rect, 
            4
    );

    Player* player = player_ptr.get();

    Map mapa;
    mapa.addEntity(std::move(player_ptr));

    SDL_Texture* block = win.loadTexture("res/gfx/brackeys_platformer_assets/sprites/block.png");
    for (int i = 0; i < 2; i++) {
        auto rec = std::make_unique<Rectangle>(
                block,
                vec2f(400 * i, i * 300),
                200,
                300
        );
        mapa.addRectangle(std::move(rec), 0);
    }
    {
        auto rec1 = std::make_unique<Rectangle>(
                block,
                vec2f(0, HEIGHT - 100),
                300,
                100
        );
        mapa.addRectangle(std::move(rec1), 1);

        auto rec2 = std::make_unique<Rectangle>(
                block,
                vec2f(100, 0),
                500,
                100
        );
        mapa.addRectangle(std::move(rec2), 1);
    }

    SDL_Texture* background_texture = win.loadTexture("res/gfx/forest/Background/Background.png");
    auto background = std::make_unique<Rectangle>(background_texture, vec2f(0, 0), WIDTH, HEIGHT);



    KeyHandler key_handler;
    bool running = true;
    SDL_Event event;

    uint64_t currentFrame = 0;
    uint64_t last_frame_time = 1;
    SDL_Delay(1000);
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


        bool R_RELEASED = key_handler.is_released(SDL_SCANCODE_RIGHT, SDL_GetTicks(), 0); 
        bool L_RELEASED = key_handler.is_released(SDL_SCANCODE_LEFT, SDL_GetTicks(), 0); 

        bool R_PRESSED = key_handler.is_pressed(SDL_SCANCODE_RIGHT, SDL_GetTicks(), MILLISECONDS_TOLERANCE); 
        bool L_PRESSED = key_handler.is_pressed(SDL_SCANCODE_LEFT, SDL_GetTicks(), MILLISECONDS_TOLERANCE); 

        bool SPACE_PRESSED = key_handler.is_pressed(SDL_SCANCODE_SPACE, SDL_GetTicks(), 0); 
        bool SPACE_RELEASED = key_handler.is_released(SDL_SCANCODE_SPACE, SDL_GetTicks(), 0); 

        if (player->grounded) {
            if (SPACE_PRESSED) {
                std::cout << "BOOSTING" << std::endl;
                player->boost();
                player->set_vel(vec2f(0, 0));
            } else if (SPACE_RELEASED) {
                //std::cout << "SPACE IS RELEASED" << std::endl;
                player->jump();
            } else {
                if (L_PRESSED && R_PRESSED) {
                    player->set_vel(vec2f(0, (player->vel).y));
                } else if (L_PRESSED) {
                    //std::cout << "LEFT IS PRESSED" << std::endl;
                    player->set_vel(vec2f(-PLAYER_X_VELOCITY, (player->vel).y));
                } else if (R_PRESSED) {
                    //std::cout << "RIGHT IS PRESSED" << std::endl;
                    player->set_vel(vec2f(PLAYER_X_VELOCITY, (player->vel).y));
                } else if (L_RELEASED) {
                    //std::cout << "LEFT IS RELEASED" << std::endl;
                    player->set_vel(vec2f(0, (player->vel).y));
                } else if (R_RELEASED) {
                    //std::cout << "RIGHT IS RELEASED" << std::endl;
                    player->set_vel(vec2f(0, (player->vel).y));
                }
            }

        }




        player->set_face();
        uint32_t scene = player->scene;

        win.clear();
        win.renderRectangle(background.get());
        win.setRenderTarget(background.get());

        mapa.move(scene);
        win.render(mapa, scene);

        win.display();

        uint64_t frame_time = SDL_GetTicks() - first_frame + 1;
        player->time_factor = last_frame_time;

        last_frame_time = frame_time;
    }


    SDL_Quit();
	return 0;
}
