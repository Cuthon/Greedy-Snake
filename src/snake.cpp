#include "snake.h"
#include "food.h"
#include "wall.h"
#include "drawer.h"

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
	here.x = COL / 2 - SCALE/2;
	here.y = ROW / 2 - SCALE/2;
	body.push_front(here);
	Map.setCondit(here.x, here.y, SNAKE_TAIL);
	drawTail(here);

	for (int i = 1; i < length-1; ++i) {
		here.x += SCALE;
		body.push_front(here);
		Map.setCondit(here.x, here.y, SNAKE_BODY);
		drawBody(here);
	}
	here.x += SCALE;
	body.push_front(here);
	Map.setCondit(here.x, here.y, SNAKE_HEAD);
	drawHead(here);
}

int snake::move()
{
	int res = 0;
	location now = body.front();	//获取蛇头位置
	switch (toward) {	
	case LEFT:
		now.x -= SCALE;
		res = update(now);			//更新当前状态
		break;
	case RIGHT:
		now.x += SCALE;
		res = update(now);
		break;
	case UP:
		now.y -= SCALE;
		res = update(now);
		break;
	case DOWN:
		now.y += SCALE;
		res = update(now);
		break;
	}
	return res;
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
	for (size_t i = 1; i < body.size()-1; i++) {
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
		case CHICKEN:grade += 20; break;
		case GOLDAP:grade += 50; break;
		}
		Map.setCondit(head.x, head.y, SNAKE_HEAD);		//把头的位置设置为蛇表示吃了食物
		return true;
	}
	else return false;
}

int snake::snakelen()
{
	return length;
}

double snake::getSpeed(){
	speed = accFactor * (5 + 5 * length/(20.0 + length));
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
		clearBody(body[i]);
		transparentimage(body[i].x - SCALE/2, body[i].y - SCALE/2, 
			drawer::GetInstance()->imgMap["Item_apple"]);		//将食物在地图上画出来
	}
	bool flag = reInit();
	return flag;
}

bool snake::is_snake(int x, int y){
	return Map.getCondit(x, y) >= SNAKE_HEAD && Map.getCondit(x, y) <= SNAKE_TAIL;
}

/*以下是私有部分*/
void snake::drawHead(const location& here)
{
	clearBody(here);
	switch (toward)
	{
	case LEFT: 
		transparentimage(here.x - SCALE/2, here.y - SCALE/2, drawer::GetInstance()->imgMap["head_left"]);
		break;
	case RIGHT:
		transparentimage(here.x - SCALE/2, here.y - SCALE/2, drawer::GetInstance()->imgMap["head_right"]);
		break;
	case UP:
		transparentimage(here.x - SCALE/2, here.y - SCALE/2, drawer::GetInstance()->imgMap["head_up"]);
		break;
	case DOWN:
		transparentimage(here.x - SCALE/2, here.y - SCALE/2, drawer::GetInstance()->imgMap["head_down"]);
		break;
	}
}

void snake::drawBody(const location& here)
{
	// setfillcolor(YELLOW);
	// setlinecolor(RED);
	// fillrectangle(here.x - SCALE/2, here.y - SCALE/2, here.x + SCALE/2, here.y + SCALE/2);
	clearBody(here);
	if (body[1].x == here.x && body[1].y == here.y){
		location front = body[0];
		location next = body[2];
		if(front.y == here.y && here.y == next.y){
			transparentimage(here.x - SCALE/2, here.y - SCALE/2, drawer::GetInstance()->imgMap["body_horizen"]);
		}
		else if(front.x == here.x && here.x == next.x){
			transparentimage(here.x - SCALE/2, here.y - SCALE/2, drawer::GetInstance()->imgMap["body_vert"]);
		}
		else if((toward==DOWN && next.x<here.x) || (toward==LEFT && next.y>here.y)){
			transparentimage(here.x - SCALE/2, here.y - SCALE/2, drawer::GetInstance()->imgMap["turn_ru"]);
		}
		else if((toward==UP && next.x<here.x) || (toward==LEFT && next.y<here.y)){
			transparentimage(here.x - SCALE/2, here.y - SCALE/2, drawer::GetInstance()->imgMap["turn_rd"]);
		}
		else if((toward==UP && next.x>here.x) || (toward==RIGHT && next.y<here.y)){
			transparentimage(here.x - SCALE/2, here.y - SCALE/2, drawer::GetInstance()->imgMap["turn_ld"]);
		}
		else if((toward==DOWN && next.x>here.x) || (toward==RIGHT && next.y>here.y)){
			transparentimage(here.x - SCALE/2, here.y - SCALE/2, drawer::GetInstance()->imgMap["turn_lu"]);
		}
			
	}
	else{
		transparentimage(here.x - SCALE/2, here.y - SCALE/2, drawer::GetInstance()->imgMap["body_horizen"]);
	}
}

void snake::drawTail(const location& here){
	clearBody(here);
	if (body.size()>1){
		int pos = body.size()-1;
		location front = body[pos-1];
		if(front.x == here.x-SCALE && front.y == here.y){
			transparentimage(here.x - SCALE/2, here.y - SCALE/2, drawer::GetInstance()->imgMap["tail_r"]);
		}
		else if(front.x == here.x+SCALE && front.y == here.y){
			transparentimage(here.x - SCALE/2, here.y - SCALE/2, drawer::GetInstance()->imgMap["tail_l"]);
		}
		else if(front.x == here.x && front.y == here.y+SCALE){
			transparentimage(here.x - SCALE/2, here.y - SCALE/2, drawer::GetInstance()->imgMap["tail_u"]);
		}
		else if(front.x == here.x && front.y == here.y-SCALE){
			transparentimage(here.x - SCALE/2, here.y - SCALE/2, drawer::GetInstance()->imgMap["tail_d"]);
		}
	}
	else{
		transparentimage(here.x - SCALE/2, here.y - SCALE/2, drawer::GetInstance()->imgMap["tail_l"]);
	}
}

void snake::clearBody(const location& here)
{
	clearrectangle(here.x - SCALE/2, here.y - SCALE/2, here.x + SCALE/2, here.y + SCALE/2);
}

/*比较重要的函数，更新蛇身队列*/
int snake::update(const location& now)
{
	int res = 0;
	Map.setCondit(body.front().x, body.front().y, SNAKE_BODY);		// 先前的蛇头变为蛇身
	body.push_front(now);							// 蛇身队列中增加蛇头位置

	/*判断蛇头位置情况*/
	if (!isDead())	// 不死才进行处理
	{
		if (Map.getCondit(now.x, now.y) >= SNAKE_HEAD && Map.getCondit(now.x, now.y) <= SNAKE_TAIL) {
			// 进入此处说明当前蛇头位置与未更新的蛇身重合
			location tail = body.back();
			if (now.x == tail.x && now.y == tail.y) {	//如果刚好要咬到尾巴不算死亡			
				body.pop_back();						//队列层面清除蛇尾以防后面判断错误		
			}
			else return res = 2;				//不是尾巴就死了，退出函数
		}

		else {
			if (!eatFood()) {			// 没吃到食物时才执行以下操作
				Map.setCondit(now.x, now.y, SNAKE_HEAD);		// 蛇头设置为SNAKE状态		
				location tail = body.back();		
				clearBody(tail);								//屏幕显示方面清除蛇尾
				body.pop_back();								//队列层面清除蛇尾		
				Map.setCondit(tail.x, tail.y, EMPTY);			//地图方块层面清除蛇尾
				Map.setCondit(body.back().x, body.back().y, SNAKE_TAIL);	
				drawTail(body.back());							// 画新蛇尾
			}
			else res = 1;
		}

		drawBody(body[1]);							// 画新蛇身
		drawHead(now);								// 画新蛇头
	}
	else{
		res = 2;
	}

	return res;
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
	location pos;

	int protect = 0;
	while (protect < 500) {
		int X = rand() % (COL / SCALE);
		int Y = rand() % (ROW / SCALE);
		pos.x = SCALE * X + SCALE/2;
		pos.y = SCALE * Y + SCALE/2;
		if (Map.getCondit(pos.x, pos.y) == EMPTY && Map.getCondit(pos.x + SCALE, pos.y) == EMPTY) {
			Map.setCondit(pos.x, pos.y, SNAKE_TAIL);
			body.push_front(pos);
			drawTail(pos);

			pos.x += SCALE;
			Map.setCondit(pos.x, pos.y, SNAKE_HEAD);
			body.push_front(pos);
			drawHead(pos);
			break;
		}
		else protect++;
	}
	if (protect >= 500)return false;		//如果500次都生成不了，那就当没有空间了
	else return true;						//否则生成成功返回true
}