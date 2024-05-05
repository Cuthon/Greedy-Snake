#include "snake.h"
#include "wall.h"
#include "food.h"
#include "GameEngine.h"

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <conio.h>
#include <Windows.h>
#include <graphics.h>

using namespace std;

GameEngine* GameEngine::_instance = nullptr;

GameEngine* GameEngine::GetInstance(){
	if(_instance == nullptr){
		_instance = new GameEngine(0);
	}
	return _instance;
}

void GameEngine::Destory(){
	if(_instance != nullptr){
		delete _instance;
		_instance = nullptr;
	}
}

void GameEngine::SetState(int cond){
	state = cond;
}

int GameEngine::Menu()
{
	system("cls");
	cout << "*************** 贪吃蛇大作战 ***************" << endl;
	cout << "*                 1.经典版                 *" << endl;
	cout << "*                 2.地形版                 *" << endl;
	cout << "*                 3.趣味版                 *" << endl;
	cout << "*                 4.历史记录               *" << endl;
	cout << "*                 5.游戏说明               *" << endl;
	cout << "*                 0.退出游戏               *" << endl;
	cout << "********************************************" << endl;
	cout << "做出你的选择<0-5>:";
	char choice = getchar();
	state = choice - '0';
	return state;
}

void GameEngine::Execute(){
	switch(state){
		case 1:
		case 2:
		case 3:
			execute_local(); break;
		case 4:
			readRecord(); break;
		case 5:
			help(); break;
		default:
			return;
	}
}

/*游戏执行函数*/
void GameEngine::execute_local()
{
	ExMessage msg;

	char user[21];
	cout << "请输入您的用户名，不超过20个字符：";
	cin >> user;
	ofstream fout("history.dat", ios::app | ios::binary);

	initgraph(COL + 300, ROW + 20);
	drawUI();
	switch (state)
	{
	case 1:
		outtextxy(COL + 40, 50, _T("当前版本：经典版"));
		break;
	case 2:
		outtextxy(COL + 40, 50, _T("当前版本：地形版"));
		break;
	case 3:
		outtextxy(COL + 40, 50, _T("当前版本：趣味版"));
		break;
	default:
		break;
	}

	outtextxy(COL + 40, 250, _T("历史最高分："));
	int best = bestScore(state); // 获取当前版本的最高分
	drawScore(best);			 // 将最高分在屏幕上输出

	Map.initWall();
	snake baby(RIGHT, 3);
	baby.init();
	baby.show();

	int num = Snack.newFood();
	int eaten = 0;
	int death = 0;

	clock_t start = clock();
	while (1)
	{
		show_time(start);
		if (peekmessage(&msg, EX_CHAR))
		{
			flushmessage();
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

			if (msg.vkcode == VK_ESCAPE){
				if (IDYES == MessageBox(NULL, _T("确定要退出吗？"), _T("提示"), MB_YESNO | MB_SYSTEMMODAL))
					break; // 不玩了就退出
			}
			
		}
		baby.move();
		if (baby.isDead())
		{
			if (state == 1)
				break;
			else if (state == 2)
			{
				Snack.renew();
				eaten = 0;
				num = 1;
				if (!baby.beWall())
					break; // 没有空间了，游戏结束
				if (IDNO == MessageBox(NULL, _T("你撞死了，尸体将会变成墙，还要继续玩吗？"), _T("提示"), MB_YESNO | MB_SYSTEMMODAL))
					break; // 不玩了就退出
			}
			else if (state == 3)
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
		Sleep(1000 / baby.getSpeed());
	}

	showInform(baby.grade);

	fout << 1 << ' ' << user << ' ' << baby.grade << endl;
	fout.close(); // 操作完关闭文件
	flushmessage();
	closegraph();
}

void GameEngine::readRecord(){
	system("cls");
	ofstream outfile("history.dat", ios::out | ios::app); // 如果文件不存在，创建文件
	outfile.close();									  // 工具流，创建完就关掉

	ifstream fin("history.dat", ios::in | ios::binary);
	int edition;
	int score;
	int lineNum = 1;
	char name[20];

	char ch;
	fin >> ch;
	if (fin.eof())
	{
		cout << "暂无记录，快去冲分吧！" << endl;
		cout << "\n按任意键继续..." << endl;
		_getch();
		return;
	}
	fin.seekg(0, ios::beg);

	while (!fin.eof())
	{

		fin >> edition >> name >> score;
		if (fin.fail())
			break;
		cout << lineNum++ << '.';

		switch (edition)
		{
		case 1:
			cout << "版本：经典版";
			break;
		case 2:
			cout << "版本：地形版";
			break;
		case 3:
			cout << "版本：趣味版";
			break;
		}
		cout << " 用户名：" << name << " 得分" << score << endl;
		fin.ignore(100, '\n'); // 跳到下一行
	}
	fin.close(); // 操作完关闭文件

	cout << "\n1.删除记录  2.更改昵称  0.退回菜单" << endl;
	cout << "请选择操作：";
	switch (_getche())
	{
	case '1':
		cout << "\n你可以输入某条记录所在的行数以删除它，输入0放弃操作" << endl;
		while (1)
		{
			if (!delRecord())
				break;
		}
		break;
	case '2':
		changeName();
		break;
	case '0':
		break;
	}

	cout << "\n按任意键继续..." << endl;
	_getch();
}

bool GameEngine::delRecord()
{
	int lineNum;
	cin >> lineNum;
	if (lineNum == 0)
		return false;

	ifstream fin("history.dat", ios::in | ios::binary); // 打开文件
	char lineContent[100];
	string fileData = "";

	int i = 1;
	while (fin.getline(lineContent, 100, '\n'))
	{
		if (i != lineNum)
		{
			fileData += lineContent;
			fileData += '\n';
		}
		++i;
	}
	fin.close();

	ofstream fout("history.dat", ios::out | ios::binary);
	fout << fileData;
	fout.close();
	cout << "第" << lineNum << "行记录已经删除" << endl;

	cout << "是否继续?(y/n):";
	if (_getche() == 'y' || _getche() == 'Y')
		return true;
	else
		return false;
}

/*更改用户名时使用*/
void replaceString(string &origin, string old_value, string new_value)
{
	/* 该函数用于对origin全文查找出现的old_value 并用new_value替换 */
	for (string::size_type pos(0); pos != string::npos; pos += new_value.length())
	{
		if ((pos = origin.find(old_value, pos)) != string::npos)
			origin.replace(pos, old_value.length(), new_value);
		else
			break;
	}
}

void GameEngine::changeName()
{
	ifstream fin("history.dat", ios::in | ios::binary);
	string old_name, new_name;
	cout << "\n请输入原用户名和更改后的用户名:" << endl;
	cin >> old_name >> new_name;

	ostringstream tmp;
	tmp << fin.rdbuf();			// 将文件全部读入字符串流
	string content = tmp.str(); // 将文件全部读入string字符串
	fin.close();				// 操作完文件后关闭文件句柄

	replaceString(content, old_name, new_name);
	ofstream fout("history.dat", ios::out | ios::binary);
	fout << content;
	cout << "更改成功！" << endl;
}

void GameEngine::help()
{
	system("cls");

	cout << "**************************** 游戏规则 *******************************" << endl;
	cout << "*                                                                   *" << endl;
	cout << "*                            基本操作                               *" << endl;
	cout << "*                   w:向上 a:向左 s:向下 d:向右                     *" << endl;
	cout << "*                                                                   *" << endl;
	cout << "*                              食物                                 *" << endl;
	cout << "*     一共有4种食物：苹果、葡萄、桃子，以及稀有的金苹果。苹果吃了加 *" << endl;
	cout << "* 5分，葡萄10分，桃子20分，金苹果加50分。蛇吃食物吃多了有力气了会越 *" << endl;
	cout << "* 爬越快，小心不要撞墙！                                            *" << endl;
	cout << "*                              玩法                                 *" << endl;
	cout << "* 1.经典版 经典版本，控制蛇吃食物得分，撞墙或咬到自己为死亡。       *" << endl;
	cout << "* 2.地形版 撞墙后蛇尸体会变成墙壁，游戏继续，死的时候可以选择退出。 *" << endl;
	cout << "* 3.趣味版 蛇有5条命，撞墙后不死，尸体变成食物，游戏继续。          *" << endl;
	cout << "*                                                                   *" << endl;
	cout << "*********************************************************************" << endl;

	cout << "\n按任意键继续..." << endl;
	_getch();
}


void GameEngine::drawUI()
{
	setbkcolor(RGB(101, 178, 62));
	cleardevice();
	settextcolor(WHITE);
	LOGFONT f;
	gettextstyle(&f); // 获取当前字体设置
	f.lfHeight = 28;
	_tcscpy_s(f.lfFaceName, _T("微软雅黑"));
	f.lfWeight = FW_MEDIUM;				// 加粗
	f.lfQuality = ANTIALIASED_QUALITY; 	// 设置输出效果为抗锯齿
	settextstyle(&f);				   	// 设置字体样式

	outtextxy(COL + 40, 100, _T("使用wasd控制移动方向"));
	outtextxy(COL + 40, 150, _T("游戏时间："));

	outtextxy(COL + 40, 300, _T("当前得分："));
	outtextxy(COL + 40, 350, _T("蛇身长度："));
}

void GameEngine::show_time(clock_t st)
{
	clock_t now = (clock() - st) / 1000;
	TCHAR s[6];
	_stprintf_s(s, _T("%d s"), now);
	outtextxy(COL + 160, 150, s);
}

void GameEngine::showInform(int score)
{
	TCHAR inform[100];
	_stprintf_s(inform, _T("游戏结束了！本次得分%d分"), score);
	MessageBox(NULL, inform, _T("游戏结束"), MB_OK | MB_SYSTEMMODAL);
}

int GameEngine::bestScore(int mode)
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

void GameEngine::drawScore(int score)
{
	TCHAR s[10];
	_stprintf_s(s, _T("%d分"), score);
	outtextxy(COL + 184, 250, s);
}
