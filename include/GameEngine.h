#pragma once

#include <time.h>

void drawUI();			 // 游戏UI
void show_time(clock_t); // 显示游戏时间
void showInform(int);	 // 显示提示窗口
int bestScore(int);		 // 用于获取历史最高分
void drawScore(int);	 // 显示最高分

char Menu();
void readRecord();
bool delRecord();
void changeName();
void help();

void Execute(int level);