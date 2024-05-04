#include <string>
#include <sstream>

#include "snake.h"
#include "wall.h"
#include "food.h"
#include "GameEngine.h"

using namespace std;
char Menu();
void readRecord();
bool delRecord();
void changeName();
void help();

int main()
{
	while (1)
	{
		system("cls");

		char ch = Menu();
		switch (ch)
		{
		case '1':
			Execute(1);
			break;
		case '2':
			Execute(2);
			break;
		case '3':
			Execute(3);
			break;
		case '4':
			readRecord();
			break;
		case '5':
			help();
			break;
		case '0':
			return 0;
		}
	}

	return 0;
}

char Menu()
{
	cout << "*************** 贪吃蛇大作战 ***************" << endl;
	cout << "*                 1.入门版                 *" << endl;
	cout << "*                 2.进阶版                 *" << endl;
	cout << "*                 3.高级版                 *" << endl;
	cout << "*                 4.历史记录               *" << endl;
	cout << "*                 5.游戏说明               *" << endl;
	cout << "*                 0.退出游戏               *" << endl;
	cout << "********************************************" << endl;
	cout << "做出你的选择<0-5>:";
	char choice = getchar();
	return choice;
}

void readRecord()
{
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
			cout << "版本：入门版";
			break;
		case 2:
			cout << "版本：进阶版";
			break;
		case 3:
			cout << "版本：高级版";
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

bool delRecord()
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

void changeName()
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

void help()
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
	cout << "* 1.入门版 经典版本，控制蛇吃食物得分，撞墙或咬到自己为死亡。       *" << endl;
	cout << "* 2.进阶版 撞墙后蛇尸体会变成墙壁，游戏继续，死的时候可以选择退出。 *" << endl;
	cout << "* 3.高级版 蛇有5条命，撞墙后不死，尸体变成食物，游戏继续。          *" << endl;
	cout << "*                                                                   *" << endl;
	cout << "*********************************************************************" << endl;

	cout << "\n按任意键继续..." << endl;
	_getch();
}