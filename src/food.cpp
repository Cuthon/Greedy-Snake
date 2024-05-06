#include "food.h"
#include "wall.h"
#include "snake.h"
#include "drawer.h"

#include <stdlib.h>
#include <time.h>
#include <graphics.h>

SnackBag Snack;

food::food(location& loc, condit cond, int fsc):
place(loc), species(cond), fscore(fsc){}

int SnackBag::newFood()
{
	srand((unsigned)time(0));
	int fcount = rand() % 5 + 1;
	int i = 0;
	while (i < fcount)
	{
		int X = rand() % (COL / SCALE);
		int Y = rand() % (ROW / SCALE);
		//�����±����ͼ������ת����ϵ,��ת���ɵ�ͼ����
		location temp(SCALE * X + SCALE/2, SCALE * Y + SCALE/2);
		if (Map.getCondit(temp.x, temp.y) == EMPTY) {		
			//�����λ��Ϊ�գ�������ʳ��
			bag.push_back(food(temp));			
			++i;
		}
	}
	resetSpecies();
	drawFood();
	return size();
}

void SnackBag::clearFood()
{
	//���������ʳ��
	for (auto it = bag.begin(); it != bag.end(); it++) {
		if (Map.getCondit(it->place.x, it->place.y) >= APPLE) {
			Map.setCondit(it->place.x, it->place.y, EMPTY);
			Map.clearBlock(it->place);
		}
	}
	bag.clear();
}

int SnackBag::size(){
	return bag.size();
}

//˽�в���
void SnackBag::drawFood()
{
	for (auto it = bag.begin(); it != bag.end(); it++){
		IMAGE item;
		switch (it->species) {
		case APPLE: 
		item = drawer::GetInstance()->imgMap["Item_apple"];
		break;
		case GRAPE:
		item = drawer::GetInstance()->imgMap["Item_purple"];
		break;
		case CHICKEN:
		item = drawer::GetInstance()->imgMap["Item_chiken"];
		break;
		case GOLDAP:
		item = drawer::GetInstance()->imgMap["Item_gapp"];
		break;
		}
		transparentimage(it->place.x-SCALE/2, it->place.y-SCALE/2, item);
	}
}

void SnackBag::resetSpecies()
{
	for (auto it = bag.begin(); it != bag.end(); it++){
		int temp = rand() % 100 + 1;		// ����1-100�������
		if (temp <= 50) {
			it->fscore = 5;
			it->species = APPLE;			// ����5�ֵ�ƻ��
		}		
		else if (temp <= 85) {
			it->fscore = 10;
			it->species = GRAPE;			// ����10�ֵ�����
		}
		else if (temp <= 95) {
			it->fscore = 20;
			it->species = CHICKEN;			// ����20�ֵļ���
		}
		else if (temp <= 100) {
			it->fscore = 50;
			it->species = GOLDAP;			// ����50�ֵĽ�ƻ��
		}
		Map.setCondit(it->place.x, it->place.y, it->species);
	}
	
}