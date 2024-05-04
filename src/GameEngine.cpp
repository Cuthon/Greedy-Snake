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
	gettextstyle(&f); // ��ȡ��ǰ��������
	f.lfHeight = 24;
	_tcscpy_s(f.lfFaceName, _T("��������"));
	f.lfQuality = ANTIALIASED_QUALITY; // �������Ч��Ϊ�����
	settextstyle(&f);				   // ����������ʽ

	outtextxy(COL + 40, 100, _T("ʹ��wasd�����ƶ�����"));
	outtextxy(COL + 40, 150, _T("��Ϸʱ�䣺"));

	outtextxy(COL + 40, 300, _T("��ǰ�÷֣�0"));
	outtextxy(COL + 40, 350, _T("�����ȣ�3"));
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
	outtextxy(COL + 40, 50, _T("��ǰ�汾�����Ű�"));
	outtextxy(COL + 40, 250, _T("��ʷ��߷֣�"));
	int best = bestScore(1); // ��ȡ��ǰ�汾����߷�
	drawScore(best);		 // ����߷�����Ļ�����

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
		Sleep(50 + 600 / baby.snakelen());
	}

	showInform(baby.grade);

	fout << 1 << ' ' << user << ' ' << baby.grade << endl;
	fout.close(); // ������ر��ļ�
	closegraph();
}
