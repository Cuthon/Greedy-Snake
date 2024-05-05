#include <stdlib.h>
#include <iostream>
#include "GameEngine.h"

GameEngine* game = GameEngine::GetInstance();

int main()
{
	int running = 1;
	while (running)
	{
		if(running = game->Menu())
			game->Execute();
	}
	game->Destory();

	return 0;
}
