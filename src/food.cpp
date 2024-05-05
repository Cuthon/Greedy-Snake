#include "food.h"
#include "wall.h"
#include "snake.h"
#include "drawer.h"

#include <stdlib.h>
#include <time.h>
#include <graphics.h>

food Snack;

int food::newFood()
{
	srand((unsigned)time(0));
	int fcount = rand() % 5 + 1;
	int i = 0;
	while (i < fcount)
	{
		int X = rand() % (COL / SCALE);
		int Y = rand() % (ROW / SCALE);
		//数组下标与地图坐标有转换关系,先转换成地图坐标
		if (Map.getCondit(SCALE * X + SCALE/2, SCALE * Y + SCALE/2) == EMPTY) {		
			//如果该位置为空，则生成食物
			place.x = SCALE * X + SCALE/2;
			place.y = SCALE * Y + SCALE/2;
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
	for (int i = 0; i < ROW / SCALE; ++i) {
		for (int j = 0; j < COL / SCALE; ++j) {
			if (Map.gameMap[i][j] >= APPLE) {
				Map.gameMap[i][j] = EMPTY;
				clearcircle(SCALE * j + SCALE/2, SCALE * i + SCALE/2, SCALE/2);
			}
		}
	}
	srand((unsigned)time(0));
	while (1) {
		int X = rand() % (COL / SCALE);
		int Y = rand() % (ROW / SCALE);
		//数组下标与地图坐标有转换关系,先转换成地图坐标
		if (Map.getCondit(SCALE * X + SCALE/2, SCALE * Y + SCALE/2) == EMPTY) {
			//如果该位置为空，则生成食物
			place.x = SCALE * X + SCALE/2;
			place.y = SCALE * Y + SCALE/2;
			setSpecies();
			drawFood();
			break;
		}
	}
}


//私有部分
void food::drawFood()
{
	IMAGE item;
	switch (fscore) {
	case 5: 
	item = drawer::GetInstance()->imgMap["Item_apple"];
	break;
	case 10:
	item = drawer::GetInstance()->imgMap["Item_purple"];
	break;
	case 20:
	item = drawer::GetInstance()->imgMap["Item_chiken"];
	break;
	case 50:
	item = drawer::GetInstance()->imgMap["Item_gapp"];
	break;
	}
	transparentimage(place.x-SCALE/2, place.y-SCALE/2, item);
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
		Map.setCondit(place.x, place.y, CHICKEN);
	}
	else if (temp <= 100) {
		fscore = 50;					//生成50分的金苹果
		Map.setCondit(place.x, place.y, GOLDAP);
	}
}