#include "food.h"
#include "wall.h"
#include "snake.h"
food Snack;

int food::newFood()
{
	srand((unsigned)time(0));
	int fcount = rand() % 5 + 1;
	int i = 0;
	while (i < fcount)
	{
		int X = rand() % (COL / 10);
		int Y = rand() % (ROW / 10);
		//数组下标与地图坐标有转换关系,先转换成地图坐标
		if (Map.getCondit(10 * X + 5, 10 * Y + 5) == EMPTY) {		
			//如果该位置为空，则生成食物
			place.x = 10 * X + 5;
			place.y = 10 * Y + 5;
			setSpecies();
			drawFood();			
			++i;
		}
	}
	return fcount;
}

void food::renew()
{
	//先清除现有食物
	for (int i = 0; i < ROW / 10; ++i) {
		for (int j = 0; j < COL / 10; ++j) {
			if (Map.gameMap[i][j] >= APPLE) {
				Map.gameMap[i][j] = EMPTY;
				clearcircle(10 * j + 5, 10 * i + 5, 5);
			}
		}
	}
	srand((unsigned)time(0));
	while (1) {
		int X = rand() % (COL / 10);
		int Y = rand() % (ROW / 10);
		//数组下标与地图坐标有转换关系,先转换成地图坐标
		if (Map.getCondit(10 * X + 5, 10 * Y + 5) == EMPTY) {
			//如果该位置为空，则生成食物
			place.x = 10 * X + 5;
			place.y = 10 * Y + 5;
			setSpecies();
			drawFood();
			break;
		}
	}
}

//私有部分
void food::drawFood()
{
	switch (fscore) {
	case 5: setfillcolor(RED); break;
	case 10:setfillcolor(RGB(165, 110, 255)); break;
	case 20:setfillcolor(RGB(234, 100, 139)); break;
	case 50:setfillcolor(RGB(250, 196, 39)); break;
	}
	solidcircle(place.x, place.y, 5);
}

void food::setSpecies()
{
	int temp = rand() % 100 + 1;		//生成1-100的随机数
	if (temp <= 50) {
		fscore = 5;						//生成5分的苹果
		Map.setCondit(place.x, place.y, APPLE);
	}		
	else if (temp <= 85) {
		fscore = 10;					//生成10分的葡萄
		Map.setCondit(place.x, place.y, GRAPE);
	}
	else if (temp <= 95) {
		fscore = 20;					//生成20分的桃子
		Map.setCondit(place.x, place.y, PEACH);
	}
	else if (temp <= 100) {
		fscore = 50;					//生成50分的金苹果
		Map.setCondit(place.x, place.y, GOLDAP);
	}
}