#include"pch.h"
#include"Bomb.h"
#include"resource.h"

CBomb::CBomb()
{
	// 导动画图片
	bomb_anim[0].LoadBitmap(IDB_BOMB1);
	bomb_anim[1].LoadBitmap(IDB_BOMB2);
	bomb_anim[2].LoadBitmap(IDB_BOMB3);
	bomb_anim[3].LoadBitmap(IDB_BOMB4);
	bomb_anim[4].LoadBitmap(IDB_BOMB5);
	bomb_anim[5].LoadBitmap(IDB_BOMB6);
	bomb.LoadBitmap(IDB_BOOM);
	Init();
}
void CBomb::Init()
{
	bomb_block_num = -1;
	bomb_pos[0] = -1, bomb_pos[1] = -1;
}
void CBomb::BombAnimation(CDC* pDC)
{
	for (int i = 0; i < anim_num; i++)
	{
		CDC dc;
		dc.CreateCompatibleDC(pDC);
		CBitmap* now = dc.SelectObject(&bomb_anim[i]);
		TransparentBlt(pDC->m_hDC, map_pos[bomb_block_num][0] - 5, map_pos[bomb_block_num][1] - 25, bomb_anim_width, bomb_anim_height, dc.m_hDC, 0, 0,bomb_anim_width, bomb_anim_height, RGB(255, 255, 255));//参数
		dc.SelectObject(now);
		pDC->BitBlt(map_pos[bomb_block_num][0] - 5, map_pos[bomb_block_num][1] - 25, bomb_anim_width, bomb_anim_height, &dc, 0, 0, SRCCOPY);
		Sleep(bomb_anim_sleep);
	}
	bomb_block_num = -1;
	bomb_pos[0] = -1, bomb_pos[1] = -1;
	return;
}
void CBomb::DrawBomb(CDC* pDC)
{
	if (bomb_block_num <= 0)return;
	CDC dc;
	dc.CreateCompatibleDC(pDC);
	CBitmap* now = dc.SelectObject(&bomb);
	TransparentBlt(pDC->m_hDC, map_pos[bomb_block_num][0]-5, map_pos[bomb_block_num][1]-5, bomb_width, bomb_height, dc.m_hDC, 0, 0, bomb_width, bomb_height, RGB(255, 255, 255));
	dc.SelectObject(now);
	pDC->BitBlt(map_pos[bomb_block_num][0]-5, map_pos[bomb_block_num][1]-5, bomb_width, bomb_height, &dc, 0, 0, SRCCOPY);
}