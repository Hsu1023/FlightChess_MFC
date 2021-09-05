#pragma once
#include"pch.h"
#include"data.h"

class CBomb
{
public:
	CBitmap bomb;
	CBitmap bomb_anim[6];

public:
	int bomb_block_num;//Õ¨µ¯Î»ÖÃ
	int bomb_pos[2];

public:
	const int bomb_width = 43;
	const int bomb_height = 51;

	const int bomb_anim_width = 32;
	const int bomb_anim_height = 64;

	const int bomb_anim_sleep = 80;

	const int anim_num = 6;

public:
	CBomb();
	void Init();
	void BombAnimation(CDC* pDC);
	void DrawBomb(CDC* pDC);
};
