#ifndef AI_H
#define AI_H


#include"pch.h"


class AI
{
public:
	
	CBitmap aiLogo[4];//AI��ͼ�� Ŀǰ������ΪС�ɻ�
	CBitmap aiCtrl[2];//����AI�Ĺؿ�ͼƬ

public:
	bool enterFlag;
	bool on[4];//�ж�AI�Ƿ�����

public:
	const int aiLogo_pos[4][2] = { {710,333},{710,398},{710,463},{710,528} };
	const int aiLogo_h = 45, aiLogo_w = 45;
	const int aiCtrl_pos[4][2] = { {770,320},{770,385},{770,450},{770,515} };
	const int aiCtrl_h = 60, aiCtrl_w = 130;

public:
	AI();
	void Init();//���AI�ĳ�ʼ��������ͼƬ
	void DrawCtrl(CDC *pDC);//��Ctrl ��Ϊÿһ����Ϸ�غ�Ҫ��һ�θ��¿��أ����������ֿ�
	void DrawLogo(CDC* pDC);//��logo
	//��Ҫ˼·Ϊ�ж�now_player��AI��״̬����Ϊtrue�������Action���һ���غ�
	//void Action();
};

#endif // !AI_H

//����Ϸÿһ�ν��е�ʱ�򣬼��һ��ai��״̬
