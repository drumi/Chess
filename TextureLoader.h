#pragma once
#include <SDL2/SDL.h>

class TextureLoader
{
    private:
    TextureLoader(){}

    public:
    static SDL_Texture* Load(SDL_Renderer* renderer, char const* path);
};