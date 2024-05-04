#pragma once
#define ROW 480
#define COL 640
#include "food.h"
enum condit { EMPTY, SNAKE, WALL, APPLE, GRAPE, PEACH, GOLDAP };	//��ö�ٱ�ʾ��ͼ��ÿ�������״̬

class Wall {
public:
	void initWall();						//��ʼ����Ϸ��ͼ
	void drawWall(int x, int y);			//��ǽ��
	condit getCondit(int x, int y);			//��ȡ��ͼ�����״̬
	void setCondit(int x, int y, condit);	//���õ�ͼ�����״̬
	friend void food::renew();

private:
	condit gameMap[ROW / 10][COL / 10];		//��Ϸ��ͼ���飬���ÿ����ͼ������������
};

extern Wall Map;
