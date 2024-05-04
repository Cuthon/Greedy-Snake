#include "snake.h"
#include "wall.h"
#include "food.h"
#include "GameEngine.h"

#include <graphics.h>

void drawUI()
{
	setbkcolor(RGB(101, 178, 62));
	cleardevice();
	settextcolor(WHITE);
	LOGFONT f;
	gettextstyle(&f); // 获取当前字体设置
	f.lfHeight = 24;
	_tcscpy_s(f.lfFaceName, _T("方正舒体"));
	f.lfQuality = ANTIALIASED_QUALITY; // 设置输出效果为抗锯齿
	settextstyle(&f);				   // 设置字体样式

	outtextxy(COL + 40, 100, _T("使用wasd控制移动方向"));
	outtextxy(COL + 40, 150, _T("游戏时间："));

	outtextxy(COL + 40, 300, _T("当前得分：0"));
	outtextxy(COL + 40, 350, _T("蛇身长度：3"));
}

void show_time(clock_t st)
{
	clock_t now = (clock() - st) / 1000;
	TCHAR s[6];
	_stprintf_s(s, _T("%d s"), now);
	outtextxy(COL + 160, 150, s);
}

void showInform(int score)
{
	TCHAR inform[100];
	_stprintf_s(inform, _T("游戏结束了！本次得分%d分"), score);
	MessageBox(NULL, inform, _T("游戏结束"), MB_OK | MB_SYSTEMMODAL);
}

int bestScore(int mode)
{
	int edition;
	int temp;
	int score = 0;
	ifstream fin("history.dat", ios::in | ios::binary);

	while (!fin.eof())
	{
		fin >> edition;
		if (edition == mode)
		{
			fin.ignore();
			fin.ignore(20, ' ');
			fin >> temp;
			if (temp > score)
				score = temp;
		}
		fin.ignore(100, '\n'); // 跳到下一行
	}
	fin.close(); // 操作完关闭文件
	return score;
}

void drawScore(int score)
{
	TCHAR s[10];
	_stprintf_s(s, _T("%d分"), score);
	outtextxy(COL + 184, 250, s);
}

/*游戏执行函数*/
void Execute(int level)
{
	ExMessage msg; 

	char user[21];
	cout << "请输入您的用户名，不超过20个字符：";
	cin >> user;
	ofstream fout("history.dat", ios::app | ios::binary);

	initgraph(COL + 300, ROW + 20);
	drawUI();
	outtextxy(COL + 40, 50, _T("当前版本：入门版"));
	outtextxy(COL + 40, 250, _T("历史最高分："));
	int best = bestScore(1); // 获取当前版本的最高分
	drawScore(best);		 // 将最高分在屏幕上输出

	Map.initWall();
	snake baby(RIGHT, 3);
	baby.init();

	int num = Snack.newFood();
	int eaten = 0;
	int death = 0;

	clock_t start = clock();
	while (1)
	{
		show_time(start);
		if (peekmessage(&msg, EX_CHAR))
		{
			switch (msg.ch)
			{
			case 'a':
			case 'A':
				baby.redirect(LEFT);
				break;

			case 's':
			case 'S':
				baby.redirect(DOWN);
				break;

			case 'd':
			case 'D':
				baby.redirect(RIGHT);
				break;

			case 'w':
			case 'W':
				baby.redirect(UP);
				break;
			}
		}
		baby.move();
		if (baby.isDead())
		{
			if (level == 1)
				break;
			else if (level == 2)
			{
				Snack.renew();
				eaten = 0;
				num = 1;
				if (!baby.beWall())
					break; // 没有空间了，游戏结束
				if (IDNO == MessageBox(NULL, _T("你撞死了，尸体将会变成墙，还要继续玩吗？"), _T("提示"), MB_YESNO | MB_SYSTEMMODAL))
					break; // 不玩了就退出
			}
			else if (level == 3)
			{
				death++;
				TCHAR life = 5 - death + 48;
				outtextxy(COL + 184, 200, life);

				Snack.renew(); // 重设食物位置
				eaten = 0;
				num = 1 + baby.snakelen();		  // 蛇身都变成食物了，再加上生成的一个食物
				if (!baby.beFood() || death >= 5) // 没有空间或者撞墙超过5次了，游戏结束
					break;
			}
		}

		if (baby.eatFood())
		{
			eaten++; // 每吃掉一个食物计数器就+1
			if (eaten >= num)
			{
				num = Snack.newFood(); // 如果食物吃完才生成新食物
				eaten = 0;			   // 吃食计数器归零
			}
			baby.show();
		}

		if (baby.grade > best)
			drawScore(baby.grade); // 历史最高分随当前得分同步
		Sleep(50 + 600 / baby.snakelen());
	}

	showInform(baby.grade);

	fout << 1 << ' ' << user << ' ' << baby.grade << endl;
	fout.close(); // 操作完关闭文件
	closegraph();
}
