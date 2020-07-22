#include <iostream>
#include "Board.h"
#include "MoveValidator.h"

int main()
{
   Board b;
   MoveValidator::isValid(b, 1, 1, 1, 2);
   
   return 0;
}