#pragma once

#include "food.h"

#define ROW 480
#define COL 640
#define SCALE 20

enum condit { EMPTY, WALL, SNAKE_HEAD, SNAKE_BODY, SNAKE_TAIL, APPLE, GRAPE, CHICKEN, GOLDAP };	//��ö�ٱ�ʾ��ͼ��ÿ�������״̬

class Wall {
public:
	void initWall();						//��ʼ����Ϸ��ͼ
	void drawWall(int x, int y);			//��ǽ��
	condit getCondit(int x, int y);			//��ȡ��ͼ�����״̬
	void setCondit(int x, int y, condit);	//���õ�ͼ�����״̬
	friend void food::renew();

private:
	condit gameMap[ROW / SCALE][COL / SCALE];		//��Ϸ��ͼ���飬���ÿ����ͼ������������
};

extern Wall Map;
