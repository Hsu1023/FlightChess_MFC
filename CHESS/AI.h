#ifndef AI_H
#define AI_H


#include"pch.h"


class AI
{
public:
	
	CBitmap aiLogo[4];//AI的图标 目前考虑仍为小飞机
	CBitmap aiCtrl[2];//控制AI的关开图片

public:
	bool enterFlag;
	bool on[4];//判断AI是否启动

public:
	const int aiLogo_pos[4][2] = { {710,333},{710,398},{710,463},{710,528} };
	const int aiLogo_h = 45, aiLogo_w = 45;
	const int aiCtrl_pos[4][2] = { {770,320},{770,385},{770,450},{770,515} };
	const int aiCtrl_h = 60, aiCtrl_w = 130;

public:
	AI();
	void Init();//完成AI的初始化，导入图片
	void DrawCtrl(CDC *pDC);//画Ctrl 因为每一个游戏回合要调一次更新开关，所以两个分开
	void DrawLogo(CDC* pDC);//画logo
	//主要思路为判断now_player的AI的状态，若为true，则调用Action完成一个回合
	//void Action();
};

#endif // !AI_H

//在游戏每一次进行的时候，检测一下ai的状态
