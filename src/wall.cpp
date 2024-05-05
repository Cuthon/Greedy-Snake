#include "wall.h"
#include <graphics.h>
Wall Map;

void Wall::drawWall(int x, int y)
{
	setfillcolor(RGB(153, 108, 51));
	setlinecolor(RGB(101, 178, 62));
	fillrectangle(x - SCALE/2, y - SCALE/2, x + SCALE/2, y + SCALE/2);
}

/*初始化地图*/
void Wall::initWall()
{
	for (int i = 0; i < ROW / SCALE; i++) {
		for (int j = 0; j < COL / SCALE; j++) {
			if (i == 0 || j == 0 || i == ROW / SCALE - 1 || j == COL / SCALE - 1) {
				gameMap[i][j] = WALL;		//如果是边界，则设置为墙壁
			}
			else gameMap[i][j] = EMPTY;		//不是边界则设置为空
		}
	}

	for (int i = 0; i < ROW / SCALE; i++) {
		for (int j = 0; j < COL / SCALE; j++) {
			if (gameMap[i][j] == WALL)
				drawWall(SCALE * j + SCALE/2, SCALE * i + SCALE/2);
		}
	}
}

condit Wall::getCondit(int x, int y)
{
	int X = (x - SCALE/2) / SCALE;
	int Y = (y - SCALE/2) / SCALE;
	return gameMap[Y][X];
}

void Wall::setCondit(int x, int y, condit s)
{
	int X = (x - SCALE/2) / SCALE;
	int Y = (y - SCALE/2) / SCALE;
	gameMap[Y][X] = s;
}