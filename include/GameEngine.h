#pragma once

#include <time.h>

class GameEngine{
public:
    static GameEngine* GetInstance();
    static void Destory();
    void SetState(int cond);
    int Menu();
    void Execute();

private:
    static GameEngine* _instance;
    GameEngine(int cond);
    void test();

    void execute_local();
    void readRecord();
    void help();

    void drawUI();			 // 游戏UI
    void show_time(clock_t); // 显示游戏时间
    void showInform(int);	 // 显示提示窗口
    int bestScore(int);		 // 用于获取历史最高分
    void drawScore(int);	 // 显示最高分    
    bool delRecord();
    void changeName();

    int state;
};
