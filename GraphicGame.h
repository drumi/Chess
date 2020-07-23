#pragma once

#include <SDL2/SDL.h>
#include <unordered_map>
#include "Game.h"

 // -lmingw32 -lSDL2main -lSDL2

class GraphicGame
{
    private:
    int const BORDER_PIXEL_OFFSET;
    int const SQUARE_SIZE;
    bool m_isRunning;
    Game m_game;
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;
    std::unordered_map<char const*, SDL_Texture*> textures;

    void loadTextures();

    public:
    GraphicGame(int x, int y, int w);
    ~GraphicGame();
    void render();
    void handleEvents();
    bool isRunning() const { return m_isRunning; }
};