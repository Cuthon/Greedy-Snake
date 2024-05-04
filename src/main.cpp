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