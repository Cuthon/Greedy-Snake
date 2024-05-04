#include "wall.h"
#include <graphics.h>
Wall Map;

void Wall::drawWall(int x, int y)
{
	setfillcolor(RGB(153, 108, 51));
	setlinecolor(RGB(101, 178, 62));
	fillrectangle(x - 5, y - 5, x + 5, y + 5);
}

/*初始化地图*/
void Wall::initWall()
{
	for (int i = 0; i < ROW / 10; i++) {
		for (int j = 0; j < COL / 10; j++) {
			if (i == 0 || j == 0 || i == ROW / 10 - 1 || j == COL / 10 - 1) {
				gameMap[i][j] = WALL;		//如果是边界，则设置为墙壁
			}
			else gameMap[i][j] = EMPTY;		//不是边界则设置为空
		}
	}

	for (int i = 0; i < ROW / 10; i++) {
		for (int j = 0; j < COL / 10; j++) {
			if (gameMap[i][j] == WALL)
				drawWall(10 * j + 5, 10 * i + 5);
		}
	}
}

condit Wall::getCondit(int x, int y)
{
	int X = (x - 5) / 10;
	int Y = (y - 5) / 10;
	return gameMap[Y][X];
}

void Wall::setCondit(int x, int y, condit s)
{
	int X = (x - 5) / 10;
	int Y = (y - 5) / 10;
	gameMap[Y][X] = s;
}