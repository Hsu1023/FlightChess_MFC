#include"pch.h"
#include"AI.h"
#include"resource.h"
using namespace std;

AI::AI()
{
	aiLogo[0].LoadBitmapW(IDB_GREENPLANE);
	aiLogo[1].LoadBitmapW(IDB_REDPLANE);
	aiLogo[2].LoadBitmapW(IDB_YELLOWPLANE);
	aiLogo[3].LoadBitmapW(IDB_BLUEPLANE);
	aiCtrl[0].LoadBitmapW(IDB_OFF);//关的图片
	aiCtrl[1].LoadBitmapW(IDB_ON);//开的图片

	Init();
}

void AI::Init()
{
	for (int i = 0; i < 4; i++)
	{
		on[i] = false;
	}
	enterFlag = false;
}
void AI::DrawCtrl(CDC *pDC)
{
	CDC dc;
	dc.CreateCompatibleDC(pDC);
	//画ctrl   
	
	for (int i = 0; i < 4; i++)
	{
		dc.SelectObject(aiCtrl[on[i]]);
		pDC->BitBlt(aiCtrl_pos[i][0], aiCtrl_pos[i][1], aiCtrl_w, aiCtrl_h, &dc, 0, 0, SRCCOPY);
	}
}
void AI::DrawLogo(CDC* pDC)
{
	CDC dc;
	dc.CreateCompatibleDC(pDC);
	for (int i = 0; i < 4; i++)
	{
		dc.SelectObject(aiLogo[i]);
		pDC->BitBlt(aiLogo_pos[i][0], aiLogo_pos[i][1], aiLogo_w, aiLogo_h, &dc, 0, 0, SRCCOPY);
	}
}