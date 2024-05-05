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

    void drawUI();			 // ��ϷUI
    void show_time(clock_t); // ��ʾ��Ϸʱ��
    void showInform(int);	 // ��ʾ��ʾ����
    int bestScore(int);		 // ���ڻ�ȡ��ʷ��߷�
    void drawScore(int);	 // ��ʾ��߷�    
    bool delRecord();
    void changeName();

    int state;
};
