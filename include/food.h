#pragma once

#include "snake.h"

class food {
public:
	struct location {
		int x;
		int y;
	};
	int newFood();			//生成食物
	void renew();			//某些模式的重新生成
	friend bool snake::eatFood();

private:
	location place;			//该食物的位置
	int fscore;				//不同食物对应不同分数
	void drawFood();
	void setSpecies();		//随机设置食物的种类
};

extern food Snack;