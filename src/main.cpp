#include <stdlib.h>

#include "GameEngine.h"

using namespace std;

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
