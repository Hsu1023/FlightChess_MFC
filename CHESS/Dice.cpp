#include"pch.h"
#include"Dice.h"
#include"resource.h"
CDice::CDice()
{
	bmp_dices.LoadBitmap(IDB_DICE);
	bmp_dice[1].LoadBitmap(IDB_D1);
	bmp_dice[2].LoadBitmap(IDB_D2);
	bmp_dice[3].LoadBitmap(IDB_D3);
	bmp_dice[4].LoadBitmap(IDB_D4);
	bmp_dice[5].LoadBitmap(IDB_D5);
	bmp_dice[6].LoadBitmap(IDB_D6);
	Init();
}
void CDice::Init()
{
	num = 0;
	shaking = 0;
}

