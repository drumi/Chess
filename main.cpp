 #include <SDL2/SDL.h>
 #include "GraphicGame.h"

 // -lmingw32 -lSDL2main -lSDL2

int main( int argc, char* args[] )
{
    GraphicGame game(300, 100, 600, true, 3);
    
    while(game.isRunning())
    {
        game.render();
        game.handleEvents();
        SDL_Delay(100);
    }

    return 0;    
}
