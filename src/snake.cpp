#include "snake.h"
#include "food.h"
#include "wall.h"

#include <time.h>
#include <iostream>
#include <fstream>
#include <graphics.h>
#include <cstring>
using namespace std;

/*公有部分函数*/
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
	location now = body.front();	//获取蛇头位置
	switch (toward) {	
	case LEFT:
		now.x -= 10;
		update(now);				//更新当前状态
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

/*检查蛇是否已经死亡*/
bool snake::isDead()
{
	bool dead = false;
	location head = body.front();
	for (size_t i = 1; i < body.size(); i++) {
		if (head.x == body[i].x && head.y == body[i].y) {
			dead = true;
			body.pop_front();	//此处蛇头与某段身体已经重合，应去掉
			break;
		}
	}
	if (Map.getCondit(head.x, head.y) == WALL) {
		dead = true;
		body.pop_front();		//此处蛇头与墙已经重合，应去掉
	}

	return dead;
}

/*检查蛇是否吃到了食物*/
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
		Map.setCondit(head.x, head.y, SNAKE);		//把头的位置设置为蛇表示吃了食物
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
	_stprintf_s(temp, _T("%d"), grade);			// 高版本 VC 推荐使用 _stprintf_s 函数
	outtextxy(COL + 160, 300, temp);
	_stprintf_s(temp, _T("%d"), length);		// 高版本 VC 推荐使用 _stprintf_s 函数
	outtextxy(COL + 160, 350, temp);
}

bool snake::beWall()
{
	for (size_t i = 0; i < body.size(); ++i) {
		Map.setCondit(body[i].x, body[i].y, WALL);	//将这个位置设置为墙
		Map.drawWall(body[i].x, body[i].y);			//将墙在地图上画出来
	}
	bool flag = reInit();
	return flag;
}

bool snake::beFood()
{
	for (size_t i = 0; i < body.size(); ++i) {
		Map.setCondit(body[i].x, body[i].y, APPLE);	//将这个位置设置为食物(最低分的苹果)
		setfillcolor(RED);
		clearrectangle(body[i].x - 5, body[i].y - 5, body[i].x + 5, body[i].y + 5);
		solidcircle(body[i].x, body[i].y, 5);		//将食物在地图上画出来
	}
	bool flag = reInit();
	return flag;
}


/*以下是私有部分*/
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

/*比较重要的函数，更新蛇身队列*/
void snake::update(const location& now)
{
	body.push_front(now);				//蛇身队列中增加蛇头

	if (Map.getCondit(now.x, now.y) != WALL)	//撞墙死的情况单独考虑
	{
		if (Map.getCondit(now.x, now.y) == SNAKE) {
			location tail = body.back();
			if (now.x == tail.x && now.y == tail.y) {	//如果刚好要咬到尾巴不算死亡			
				body.pop_back();						//队列层面清除蛇尾以防后面判断错误		
			}
			else return;				//不是尾巴就死了，退出函数
		}

		else {
			drawBody(now);					//画新蛇头

			if (Map.getCondit(now.x, now.y) < APPLE) {	//没吃到食物时才执行以下操作		
				Map.setCondit(now.x, now.y, SNAKE);		//蛇头设置为SNAKE状态
				location tail = body.back();
				clearBody(tail);						//屏幕显示方面清除蛇尾
				body.pop_back();						//队列层面清除蛇尾		
				Map.setCondit(tail.x, tail.y, EMPTY);	//地图方块层面清除蛇尾
			}
		}
	}
}

/*用于进阶模式蛇的重新生成*/
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
	if (protect >= 500)return false;		//如果500次都生成不了，那就当没有空间了
	else return true;						//否则生成成功返回true
}