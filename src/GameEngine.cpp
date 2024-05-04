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

void drawUI()
{
	setbkcolor(RGB(101, 178, 62));
	cleardevice();
	settextcolor(WHITE);
	LOGFONT f;
	gettextstyle(&f); // ��ȡ��ǰ��������
	f.lfHeight = 24;
	_tcscpy_s(f.lfFaceName, _T("΢���ź�"));
	f.lfQuality = ANTIALIASED_QUALITY; // �������Ч��Ϊ�����
	settextstyle(&f);				   // ����������ʽ

	outtextxy(COL + 40, 100, _T("ʹ��wasd�����ƶ�����"));
	outtextxy(COL + 40, 150, _T("��Ϸʱ�䣺"));

	outtextxy(COL + 40, 300, _T("��ǰ�÷֣�"));
	outtextxy(COL + 40, 350, _T("�����ȣ�"));
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
	_stprintf_s(inform, _T("��Ϸ�����ˣ����ε÷�%d��"), score);
	MessageBox(NULL, inform, _T("��Ϸ����"), MB_OK | MB_SYSTEMMODAL);
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
		fin.ignore(100, '\n'); // ������һ��
	}
	fin.close(); // ������ر��ļ�
	return score;
}

void drawScore(int score)
{
	TCHAR s[10];
	_stprintf_s(s, _T("%d��"), score);
	outtextxy(COL + 184, 250, s);
}

/*��Ϸִ�к���*/
void Execute(int level)
{
	ExMessage msg;

	char user[21];
	cout << "�����������û�����������20���ַ���";
	cin >> user;
	ofstream fout("history.dat", ios::app | ios::binary);

	initgraph(COL + 300, ROW + 20);
	drawUI();
	switch (level)
	{
	case 1:
		outtextxy(COL + 40, 50, _T("��ǰ�汾�����Ű�"));
		break;
	case 2:
		outtextxy(COL + 40, 50, _T("��ǰ�汾�����װ�"));
		break;
	case 3:
		outtextxy(COL + 40, 50, _T("��ǰ�汾���߼���"));
		break;
	default:
		break;
	}

	outtextxy(COL + 40, 250, _T("��ʷ��߷֣�"));
	int best = bestScore(level); // ��ȡ��ǰ�汾����߷�
	drawScore(best);			 // ����߷�����Ļ�����

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

			flushmessage();
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
					break; // û�пռ��ˣ���Ϸ����
				if (IDNO == MessageBox(NULL, _T("��ײ���ˣ�ʬ�彫����ǽ����Ҫ��������"), _T("��ʾ"), MB_YESNO | MB_SYSTEMMODAL))
					break; // �����˾��˳�
			}
			else if (level == 3)
			{
				death++;
				TCHAR life = 5 - death + 48;
				outtextxy(COL + 184, 200, life);

				Snack.renew(); // ����ʳ��λ��
				eaten = 0;
				num = 1 + baby.snakelen();		  // �������ʳ���ˣ��ټ������ɵ�һ��ʳ��
				if (!baby.beFood() || death >= 5) // û�пռ����ײǽ����5���ˣ���Ϸ����
					break;
			}
		}

		if (baby.eatFood())
		{
			eaten++; // ÿ�Ե�һ��ʳ���������+1
			if (eaten >= num)
			{
				num = Snack.newFood(); // ���ʳ������������ʳ��
				eaten = 0;			   // ��ʳ����������
			}
			baby.show();
		}

		if (baby.grade > best)
			drawScore(baby.grade); // ��ʷ��߷��浱ǰ�÷�ͬ��
		Sleep(200 / baby.getSpeed());
	}

	showInform(baby.grade);

	fout << 1 << ' ' << user << ' ' << baby.grade << endl;
	fout.close(); // ������ر��ļ�
	closegraph();
}

char Menu()
{
	cout << "*************** ̰���ߴ���ս ***************" << endl;
	cout << "*                 1.���Ű�                 *" << endl;
	cout << "*                 2.���װ�                 *" << endl;
	cout << "*                 3.�߼���                 *" << endl;
	cout << "*                 4.��ʷ��¼               *" << endl;
	cout << "*                 5.��Ϸ˵��               *" << endl;
	cout << "*                 0.�˳���Ϸ               *" << endl;
	cout << "********************************************" << endl;
	cout << "�������ѡ��<0-5>:";
	char choice = getchar();
	return choice;
}

void readRecord()
{
	system("cls");
	ofstream outfile("history.dat", ios::out | ios::app); // ����ļ������ڣ������ļ�
	outfile.close();									  // ��������������͹ص�

	ifstream fin("history.dat", ios::in | ios::binary);
	int edition;
	int score;
	int lineNum = 1;
	char name[20];

	char ch;
	fin >> ch;
	if (fin.eof())
	{
		cout << "���޼�¼����ȥ��ְɣ�" << endl;
		cout << "\n�����������..." << endl;
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
			cout << "�汾�����Ű�";
			break;
		case 2:
			cout << "�汾�����װ�";
			break;
		case 3:
			cout << "�汾���߼���";
			break;
		}
		cout << " �û�����" << name << " �÷�" << score << endl;
		fin.ignore(100, '\n'); // ������һ��
	}
	fin.close(); // ������ر��ļ�

	cout << "\n1.ɾ����¼  2.�����ǳ�  0.�˻ز˵�" << endl;
	cout << "��ѡ�������";
	switch (_getche())
	{
	case '1':
		cout << "\n���������ĳ����¼���ڵ�������ɾ����������0��������" << endl;
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

	cout << "\n�����������..." << endl;
	_getch();
}

bool delRecord()
{
	int lineNum;
	cin >> lineNum;
	if (lineNum == 0)
		return false;

	ifstream fin("history.dat", ios::in | ios::binary); // ���ļ�
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
	cout << "��" << lineNum << "�м�¼�Ѿ�ɾ��" << endl;

	cout << "�Ƿ����?(y/n):";
	if (_getche() == 'y' || _getche() == 'Y')
		return true;
	else
		return false;
}

/*�����û���ʱʹ��*/
void replaceString(string &origin, string old_value, string new_value)
{
	/* �ú������ڶ�originȫ�Ĳ��ҳ��ֵ�old_value ����new_value�滻 */
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
	cout << "\n������ԭ�û����͸��ĺ���û���:" << endl;
	cin >> old_name >> new_name;

	ostringstream tmp;
	tmp << fin.rdbuf();			// ���ļ�ȫ�������ַ�����
	string content = tmp.str(); // ���ļ�ȫ������string�ַ���
	fin.close();				// �������ļ���ر��ļ����

	replaceString(content, old_name, new_name);
	ofstream fout("history.dat", ios::out | ios::binary);
	fout << content;
	cout << "���ĳɹ���" << endl;
}

void help()
{
	system("cls");

	cout << "**************************** ��Ϸ���� *******************************" << endl;
	cout << "*                                                                   *" << endl;
	cout << "*                            ��������                               *" << endl;
	cout << "*                   w:���� a:���� s:���� d:����                     *" << endl;
	cout << "*                                                                   *" << endl;
	cout << "*                              ʳ��                                 *" << endl;
	cout << "*     һ����4��ʳ�ƻ�������ѡ����ӣ��Լ�ϡ�еĽ�ƻ����ƻ�����˼� *" << endl;
	cout << "* 5�֣�����10�֣�����20�֣���ƻ����50�֡��߳�ʳ��Զ����������˻�Խ *" << endl;
	cout << "* ��Խ�죬С�Ĳ�Ҫײǽ��                                            *" << endl;
	cout << "*                              �淨                                 *" << endl;
	cout << "* 1.���Ű� ����汾�������߳�ʳ��÷֣�ײǽ��ҧ���Լ�Ϊ������       *" << endl;
	cout << "* 2.���װ� ײǽ����ʬ�����ǽ�ڣ���Ϸ����������ʱ�����ѡ���˳��� *" << endl;
	cout << "* 3.�߼��� ����5������ײǽ������ʬ����ʳ���Ϸ������          *" << endl;
	cout << "*                                                                   *" << endl;
	cout << "*********************************************************************" << endl;

	cout << "\n�����������..." << endl;
	_getch();
}