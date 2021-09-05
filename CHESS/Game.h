#pragma once
#include"Player.h"
#include"Dice.h"
#include"AI.h"
#include"Bomb.h"
#include"data.h"
#include"Homepage.h"

using namespace std;
class CGame {
	
public:

	AI ai;
	CBomb game_Bomb;
	CPlayer player[4]; 
	CDice dice;
	CBitmap map, rank, ranktitle, setting;
public:
	bool game_over_flag;
	bool judge_park[4];
	int now_player;
	int playing_state;//BEFOREDICE, ONDICE, AFTERDICE
	int exe_state;
public:
	int player_rank[4];//�ڼ�������ŵڼ�
	int rank_player[4];//�ڼ��ǵڼ������
	int rank_num;//���а��������
public:
	void Init();
	void InitDraw();
	void DrawBackGround(CDC* pDC);
	void Draw(CDC *pDC);
	void NewBomb();
	void Restart(CDC *pDC);
};