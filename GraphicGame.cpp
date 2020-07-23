#include "GraphicGame.h"
#include "TextureLoader.h"
#include <iostream>

GraphicGame::GraphicGame(int x, int y, int w)
:m_isRunning(true), BORDER_PIXEL_OFFSET(w / 20), SQUARE_SIZE((w - w /10)/8)
{
    SDL_Init(SDL_INIT_EVERYTHING);
    m_window = SDL_CreateWindow("Chess", x, y, w, w, SDL_WINDOW_SHOWN);
    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
    loadTextures();
}

GraphicGame::~GraphicGame()
{
    for(auto& p : textures)
        SDL_DestroyTexture(p.second);

    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
}

void GraphicGame::loadTextures()
{
    textures["background"] = TextureLoader::Load(m_renderer, "chessboard.bmp");
}

void GraphicGame::render()
{
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
    SDL_RenderClear(m_renderer);
    SDL_RenderCopy(m_renderer, textures["background"], NULL, NULL);
    SDL_RenderPresent(m_renderer);
}

void GraphicGame::handleEvents()
{
    SDL_Event event;

    while(SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            m_isRunning = false;
            break;

        case SDL_MOUSEBUTTONDOWN:
            if(event.button.button == SDL_BUTTON_LEFT)
                std::cout << event.button.x << " " << event.button.y << '\n';
            else if(event.button.button == SDL_BUTTON_RIGHT)
                m_game.undoMove();
            else if(event.button.button == SDL_BUTTON_MIDDLE)
                m_game.restart();
        
        default:
            break;
        }
    }
}