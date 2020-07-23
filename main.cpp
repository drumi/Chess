 #include <SDL2/SDL.h>
 #include "GraphicGame.h"

 // -lmingw32 -lSDL2main -lSDL2

 SDL_Renderer* m_renderer;
 SDL_Window* m_window;

int main( int argc, char* args[] )
{
    GraphicGame g(100, 100, 600, true);
    
    while(g.isRunning())
    {
        g.render();
        g.handleEvents();
        SDL_Delay(100);
    }

    return 0;    
}

/*
//Start SDL
    SDL_Init( SDL_INIT_EVERYTHING );

    m_window = SDL_CreateWindow("adsdfs", 100, 100, 400, 400, SDL_WINDOW_SHOWN);

    m_renderer =  SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);

    SDL_Surface* surface = SDL_LoadBMP("chessboard.bmp");

    SDL_Texture* texture = SDL_CreateTextureFromSurface(m_renderer, surface);

    while (1)
    {
        
        
        SDL_RenderClear(m_renderer);

        SDL_RenderCopy(m_renderer, texture, NULL, NULL);

        SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);

        SDL_RenderPresent(m_renderer);

        SDL_Event test_event;

            while(SDL_PollEvent(&test_event))
            {
                switch (test_event.type)
                {
                case SDL_QUIT:
                    return 0;
                    break;
                
                default:
                    break;
                }
            }
    }

    SDL_DestroyTexture(texture);
    SDL_DestroyWindow(m_window);
    SDL_FreeSurface(surface);
    SDL_DestroyRenderer(m_renderer);
    //Quit SDL
    SDL_Quit();
*/