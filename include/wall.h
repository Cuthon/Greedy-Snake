#pragma once

#define ROW 720
#define COL 1000		// 行列必须是SCALE的偶数倍
#define SCALE 20		// SCALE: 地图方块大小，单位为像素

enum condit { 
	EMPTY, WALL, 
	SNAKE_HEAD, SNAKE_BODY, SNAKE_TAIL, 
	APPLE, GRAPE, CHICKEN, GOLDAP 
};						// 此枚举表示地图中每个方块的状态

class location {
public:
	location(): x(0),y(0){}
	location(int i, int j): x(i),y(j){}
	int x;
	int y;
};

class Wall {
public:
	void initWall();						// 初始化游戏地图
	void drawWall(int x, int y);			// 画墙壁
	void clearBlock(const location&);		// 在画布上清除该位置为中心的地图方块
	condit getCondit(int x, int y);			// 获取地图方块的状态
	void setCondit(int x, int y, condit);	// 设置地图方块的状态
	// friend void food::renew();

private:
	condit gameMap[ROW / SCALE][COL / SCALE];		// 游戏地图数组，存放每个地图方块的数据情况
};

extern Wall Map;
