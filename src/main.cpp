#include <stdlib.h>
#include <iostream>
#include "GameEngine.h"
#include "drawer.h"

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
	// initgraph(300, 200, EW_SHOWCONSOLE);
	// putimage(0, 0, &drawer::GetInstance()->imgMap["Item_apple"]);

	// getchar();

	return 0;
}
