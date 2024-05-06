#pragma once

#include "wall.h"
#include "snake.h"
#include <vector>

class food {
public:
	food(location&, condit = APPLE, int = 5);
	location place;			// ��ʳ���λ��
	condit species;			// ʳ������
	int fscore;				// ��ͬʳ���Ӧ��ͬ����
}; 

class SnackBag {
public:
	SnackBag(){}
	int newFood();			// ����ʳ��
	void clearFood();			// ĳЩģʽ����������
	int size();				// ��ǰʳ������
	friend bool snake::beFood();

private:
	std::vector<food> bag;
	
	void drawFood();
	void resetSpecies();		// �������ʳ�������
};

extern SnackBag Snack;