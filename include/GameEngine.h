#pragma once

#include <time.h>

void drawUI();			 // ��ϷUI
void show_time(clock_t); // ��ʾ��Ϸʱ��
void showInform(int);	 // ��ʾ��ʾ����
int bestScore(int);		 // ���ڻ�ȡ��ʷ��߷�
void drawScore(int);	 // ��ʾ��߷�

char Menu();
void readRecord();
bool delRecord();
void changeName();
void help();

void Execute(int level);