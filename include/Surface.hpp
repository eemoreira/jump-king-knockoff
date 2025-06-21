#pragma once
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<string>

class Surface {
public:
	Surface(const std::string path);
    Surface(SDL_Window* window);
    bool apply_from(Surface& oth);
    SDL_Surface* getSurface();
    ~Surface();
private:
    SDL_Surface* surface;
};

