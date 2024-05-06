#pragma once

#include "wall.h"
#include "snake.h"
#include <vector>

class food {
public:
	food(location&, condit = APPLE, int = 5);
	location place;			// 该食物的位置
	condit species;			// 食物类型
	int fscore;				// 不同食物对应不同分数
}; 

class SnackBag {
public:
	SnackBag(){}
	int newFood();			// 生成食物
	void clearFood();			// 某些模式的重新生成
	int size();				// 当前食物数量
	friend bool snake::beFood();

private:
	std::vector<food> bag;
	
	void drawFood();
	void resetSpecies();		// 随机设置食物的种类
};

extern SnackBag Snack;