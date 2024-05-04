#pragma once
#include "snake.h"
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <graphics.h>

class food {
public:
	struct location {
		int x;
		int y;
	};
	int newFood();			//����ʳ��
	void renew();			//ĳЩģʽ����������
	friend bool snake::eatFood();

private:
	location place;			//��ʳ���λ��
	int fscore;				//��ͬʳ���Ӧ��ͬ����
	void drawFood();
	void setSpecies();		//�������ʳ�������
};

extern food Snack;