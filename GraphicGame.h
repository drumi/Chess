#pragma once

#include <SDL2/SDL.h>
#include <unordered_map>
#include "Game.h"

 // -lmingw32 -lSDL2main -lSDL2

class GraphicGame
{
    private:
    double const BORDER_PIXEL_OFFSET;
    double const SQUARE_SIZE;
    int m_AIDepth;
    bool m_isRunning;
    bool m_usingAI;

    Game m_game;
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;
    std::unordered_map<char const*, SDL_Texture*> textures;

    struct Move
    {
        bool hasSource = false;
        int x, y, destx, desty;
    };

    enum GameState
    {
        CHECKMATE,
        STALEMATE,
        NORMAL
    };

    Move m_nextMove;
    GameState m_gameState;

    void loadTextures();
    void move(Move& m);
    void moveAI();
    bool checkGameOver();

    public:
    GraphicGame(int x, int y, int w, bool m_usingAI = false, int AIDepth = 3);
    ~GraphicGame();
    void render();
    void handleEvents();
    bool isRunning() const { return m_isRunning; }
};