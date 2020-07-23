#include "TextureLoader.h"

SDL_Texture* TextureLoader::Load(SDL_Renderer* renderer, char const* path)
{
    SDL_Surface* surface = SDL_LoadBMP(path);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}