#pragma once
#include"pch.h"

class CDice {
public:
	CBitmap bmp_dices;
	CBitmap bmp_dice[7];

public:
	bool shaking;
	int num;
public:
	CDice();
	void Init();
};