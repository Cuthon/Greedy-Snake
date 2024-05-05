#include "snake.h"
#include "food.h"
#include "wall.h"

#include <time.h>
#include <iostream>
#include <fstream>
#include <graphics.h>
#include <cstring>
using namespace std;

/*���в��ֺ���*/
snake::snake(direct t,int len):toward(t),length(len)
{
	grade = 0;
	accFactor = 1;
	getSpeed();
}

void snake::init()
{
	location here;
	here.x = COL / 2 - 5;
	here.y = ROW / 2 - 5;
	body.push_front(here);
	drawBody(here);
	Map.setCondit(here.x, here.y, SNAKE);

	for (int i = 1; i < length; ++i) {
		here.x += 10;
		drawBody(here);
		body.push_front(here);
		Map.setCondit(here.x, here.y, SNAKE);
	}
}

void snake::move()
{
	location now = body.front();	//��ȡ��ͷλ��
	switch (toward) {	
	case LEFT:
		now.x -= 10;
		update(now);				//���µ�ǰ״̬
		break;
	case RIGHT:
		now.x += 10;
		update(now);
		break;
	case UP:
		now.y -= 10;
		update(now);
		break;
	case DOWN:
		now.y += 10;
		update(now);
		break;
	}
}

void snake::redirect(direct t)
{
	if (toward == RIGHT && t == LEFT)return;
	if (toward == LEFT && t == RIGHT)return;
	if (toward == UP && t == DOWN)return;
	if (toward == DOWN && t == UP)return;

	if (toward == t)
		accFactor = 2;
	else
		accFactor = 1;

	toward = t;
}

/*������Ƿ��Ѿ�����*/
bool snake::isDead()
{
	bool dead = false;
	location head = body.front();
	for (size_t i = 1; i < body.size(); i++) {
		if (head.x == body[i].x && head.y == body[i].y) {
			dead = true;
			body.pop_front();	//�˴���ͷ��ĳ�������Ѿ��غϣ�Ӧȥ��
			break;
		}
	}
	if (Map.getCondit(head.x, head.y) == WALL) {
		dead = true;
		body.pop_front();		//�˴���ͷ��ǽ�Ѿ��غϣ�Ӧȥ��
	}

	return dead;
}

/*������Ƿ�Ե���ʳ��*/
bool snake::eatFood()
{
	location head = body.front();
	if (Map.getCondit(head.x, head.y) >= APPLE) {	
		length += 1;
		switch (Map.getCondit(head.x, head.y)) {
		case APPLE:grade += 5; break;
		case GRAPE:grade += 10; break;
		case PEACH:grade += 20; break;
		case GOLDAP:grade += 50; break;
		}
		Map.setCondit(head.x, head.y, SNAKE);		//��ͷ��λ������Ϊ�߱�ʾ����ʳ��
		return true;
	}
	else return false;
}

int snake::snakelen()
{
	return length;
}

double snake::getSpeed(){
	speed = accFactor * (10 + length/(20.0 + length));
	return speed;
}

void snake::show()
{
	TCHAR temp[6];
	_stprintf_s(temp, _T("%d"), grade);			// �߰汾 VC �Ƽ�ʹ�� _stprintf_s ����
	outtextxy(COL + 160, 300, temp);
	_stprintf_s(temp, _T("%d"), length);		// �߰汾 VC �Ƽ�ʹ�� _stprintf_s ����
	outtextxy(COL + 160, 350, temp);
}

bool snake::beWall()
{
	for (size_t i = 0; i < body.size(); ++i) {
		Map.setCondit(body[i].x, body[i].y, WALL);	//�����λ������Ϊǽ
		Map.drawWall(body[i].x, body[i].y);			//��ǽ�ڵ�ͼ�ϻ�����
	}
	bool flag = reInit();
	return flag;
}

bool snake::beFood()
{
	for (size_t i = 0; i < body.size(); ++i) {
		Map.setCondit(body[i].x, body[i].y, APPLE);	//�����λ������Ϊʳ��(��ͷֵ�ƻ��)
		setfillcolor(RED);
		clearrectangle(body[i].x - 5, body[i].y - 5, body[i].x + 5, body[i].y + 5);
		solidcircle(body[i].x, body[i].y, 5);		//��ʳ���ڵ�ͼ�ϻ�����
	}
	bool flag = reInit();
	return flag;
}


/*������˽�в���*/
void snake::drawBody(const location& here)
{
	setfillcolor(YELLOW);
	setlinecolor(RED);
	fillrectangle(here.x - 5, here.y - 5, here.x + 5, here.y + 5);
}

void snake::clearBody(const location& here)
{
	clearrectangle(here.x - 5, here.y - 5, here.x + 5, here.y + 5);
}

/*�Ƚ���Ҫ�ĺ����������������*/
void snake::update(const location& now)
{
	body.push_front(now);				//���������������ͷ

	if (Map.getCondit(now.x, now.y) != WALL)	//ײǽ���������������
	{
		if (Map.getCondit(now.x, now.y) == SNAKE) {
			location tail = body.back();
			if (now.x == tail.x && now.y == tail.y) {	//����պ�Ҫҧ��β�Ͳ�������			
				body.pop_back();						//���в��������β�Է������жϴ���		
			}
			else return;				//����β�;����ˣ��˳�����
		}

		else {
			drawBody(now);					//������ͷ

			if (Map.getCondit(now.x, now.y) < APPLE) {	//û�Ե�ʳ��ʱ��ִ�����²���		
				Map.setCondit(now.x, now.y, SNAKE);		//��ͷ����ΪSNAKE״̬
				location tail = body.back();
				clearBody(tail);						//��Ļ��ʾ���������β
				body.pop_back();						//���в��������β		
				Map.setCondit(tail.x, tail.y, EMPTY);	//��ͼ������������β
			}
		}
	}
}

/*���ڽ���ģʽ�ߵ���������*/
bool snake::reInit()
{
	Sleep(500);
	toward = RIGHT;
	length = 2;
	clearrectangle(COL + 160, 350, COL + 240, 380);
	outtextxy(COL + 160, 350, _T("2"));

	while (body.size() >= 1) {
		body.pop_back();
	}
	srand((unsigned)time(0));
	location head;

	int protect = 0;
	while (protect < 500) {
		int X = rand() % (COL / 10);
		int Y = rand() % (ROW / 10);
		head.x = 10 * X + 5;
		head.y = 10 * Y + 5;
		if (Map.getCondit(head.x, head.y) == EMPTY && Map.getCondit(head.x + 10, head.y) == EMPTY) {
			Map.setCondit(head.x, head.y, SNAKE);
			body.push_front(head);
			drawBody(head);

			head.x += 10;
			Map.setCondit(head.x, head.y, SNAKE);
			body.push_front(head);
			drawBody(head);
			break;
		}
		else protect++;
	}
	if (protect >= 500)return false;		//���500�ζ����ɲ��ˣ��Ǿ͵�û�пռ���
	else return true;						//�������ɳɹ�����true
}