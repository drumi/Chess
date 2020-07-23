#include <iostream>
#include "Board.h"
#include "MoveValidator.h"
#include "Game.h"


int main()
{
   Game game;

   while(true)
   {
      system("cls");
      int x, y , xdest , ydest;
      
      std::cout << (game.getBoard()) << std::endl;

      std::cin >> x >> y >> xdest >> ydest;

      game.tryMove(x, y, xdest, ydest);

   }
}