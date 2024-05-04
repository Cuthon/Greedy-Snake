#include "food.h"
#include "wall.h"
#include "snake.h"
food Snack;

int food::newFood()
{
	srand((unsigned)time(0));
	int fcount = rand() % 5 + 1;
	int i = 0;
	while (i < fcount)
	{
		int X = rand() % (COL / 10);
		int Y = rand() % (ROW / 10);
		//�����±����ͼ������ת����ϵ,��ת���ɵ�ͼ����
		if (Map.getCondit(10 * X + 5, 10 * Y + 5) == EMPTY) {		
			//�����λ��Ϊ�գ�������ʳ��
			place.x = 10 * X + 5;
			place.y = 10 * Y + 5;
			setSpecies();
			drawFood();			
			++i;
		}
	}
	return fcount;
}

void food::renew()
{
	//���������ʳ��
	for (int i = 0; i < ROW / 10; ++i) {
		for (int j = 0; j < COL / 10; ++j) {
			if (Map.gameMap[i][j] >= APPLE) {
				Map.gameMap[i][j] = EMPTY;
				clearcircle(10 * j + 5, 10 * i + 5, 5);
			}
		}
	}
	srand((unsigned)time(0));
	while (1) {
		int X = rand() % (COL / 10);
		int Y = rand() % (ROW / 10);
		//�����±����ͼ������ת����ϵ,��ת���ɵ�ͼ����
		if (Map.getCondit(10 * X + 5, 10 * Y + 5) == EMPTY) {
			//�����λ��Ϊ�գ�������ʳ��
			place.x = 10 * X + 5;
			place.y = 10 * Y + 5;
			setSpecies();
			drawFood();
			break;
		}
	}
}

//˽�в���
void food::drawFood()
{
	switch (fscore) {
	case 5: setfillcolor(RED); break;
	case 10:setfillcolor(RGB(165, 110, 255)); break;
	case 20:setfillcolor(RGB(234, 100, 139)); break;
	case 50:setfillcolor(RGB(250, 196, 39)); break;
	}
	solidcircle(place.x, place.y, 5);
}

void food::setSpecies()
{
	int temp = rand() % 100 + 1;		//����1-100�������
	if (temp <= 50) {
		fscore = 5;						//����5�ֵ�ƻ��
		Map.setCondit(place.x, place.y, APPLE);
	}		
	else if (temp <= 85) {
		fscore = 10;					//����10�ֵ�����
		Map.setCondit(place.x, place.y, GRAPE);
	}
	else if (temp <= 95) {
		fscore = 20;					//����20�ֵ�����
		Map.setCondit(place.x, place.y, PEACH);
	}
	else if (temp <= 100) {
		fscore = 50;					//����50�ֵĽ�ƻ��
		Map.setCondit(place.x, place.y, GOLDAP);
	}
}