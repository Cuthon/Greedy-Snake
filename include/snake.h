#pragma once

#include <queue>

enum direct { LEFT, RIGHT, UP, DOWN };

class snake {
public:
	struct location {
		int x;
		int y;
	};
	int grade;						//当前得分
	snake(direct, int);
	void init();					//初始化蛇
	int move();						//控制蛇的移动
	void redirect(direct);			//改变蛇头朝向	
	bool isDead();					//判断是否死亡
	bool eatFood();					//判断是否吃到食物
	bool beWall();					//蛇身变成墙，进阶版使用
	bool beFood();					//蛇身变成食物，高级版用
	int snakelen();					//返回蛇长度
	double getSpeed();					//返回蛇速度
	void show();

private:
	direct toward;					//当前蛇头朝向
	int length;						//蛇身长度
	double speed;					//前进速度
	double accFactor;				//加速倍率
	std::deque <location> body;		//蛇身队列
	int update(const location&);
	void drawHead(const location&);
	void drawBody(const location&);
	void drawTail(const location&);
	void clearBody(const location&);
	bool is_snake(int, int);
	bool reInit();					//重新生成蛇
};

