#pragma once

#define ROW 720
#define COL 1000		// ���б�����SCALE��ż����
#define SCALE 20		// SCALE: ��ͼ�����С����λΪ����

enum condit { 
	EMPTY, WALL, 
	SNAKE_HEAD, SNAKE_BODY, SNAKE_TAIL, 
	APPLE, GRAPE, CHICKEN, GOLDAP 
};						// ��ö�ٱ�ʾ��ͼ��ÿ�������״̬

class location {
public:
	location(): x(0),y(0){}
	location(int i, int j): x(i),y(j){}
	int x;
	int y;
};

class Wall {
public:
	void initWall();						// ��ʼ����Ϸ��ͼ
	void drawWall(int x, int y);			// ��ǽ��
	void clearBlock(const location&);		// �ڻ����������λ��Ϊ���ĵĵ�ͼ����
	condit getCondit(int x, int y);			// ��ȡ��ͼ�����״̬
	void setCondit(int x, int y, condit);	// ���õ�ͼ�����״̬
	// friend void food::renew();

private:
	condit gameMap[ROW / SCALE][COL / SCALE];		// ��Ϸ��ͼ���飬���ÿ����ͼ������������
};

extern Wall Map;
