﻿#include <time.h>
#include "Game.h"

int main()
{
    srand(time(NULL));

    Game game;
    game.Run();
}
