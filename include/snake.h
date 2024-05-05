#pragma once

#include <queue>

enum direct { LEFT, RIGHT, UP, DOWN };

class snake {
public:
	struct location {
		int x;
		int y;
	};
	int grade;						//��ǰ�÷�
	snake(direct, int);
	void init();					//��ʼ����
	int move();						//�����ߵ��ƶ�
	void redirect(direct);			//�ı���ͷ����	
	bool isDead();					//�ж��Ƿ�����
	bool eatFood();					//�ж��Ƿ�Ե�ʳ��
	bool beWall();					//������ǽ�����װ�ʹ��
	bool beFood();					//������ʳ��߼�����
	int snakelen();					//�����߳���
	double getSpeed();					//�������ٶ�
	void show();

private:
	direct toward;					//��ǰ��ͷ����
	int length;						//������
	double speed;					//ǰ���ٶ�
	double accFactor;				//���ٱ���
	std::deque <location> body;		//�������
	int update(const location&);
	void drawHead(const location&);
	void drawBody(const location&);
	void drawTail(const location&);
	void clearBody(const location&);
	bool is_snake(int, int);
	bool reInit();					//����������
};

