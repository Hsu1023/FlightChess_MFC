#include"pch.h"
#include"Homepage.h"
#include"Resource.h"

CHomepage::CHomepage()
{
	background.LoadBitmap(IDB_BACKGROUND);
	title.LoadBitmap(IDB_TITLE);
	button[0].LoadBitmap(IDB_PLAYER1);
	button[1].LoadBitmap(IDB_PLAYER2);
	button[2].LoadBitmap(IDB_PLAYER3);
	button[3].LoadBitmap(IDB_PLAYER4);
	//
}
void CHomepage::Draw(CDC *pDC)
{
	CDC dc;
	dc.CreateCompatibleDC(pDC);
	dc.SelectObject(&background);
	pDC->BitBlt(0, 0, 2000, 1000, &dc, 0, 0, SRCCOPY);
	
	CDC dc0;
	dc0.CreateCompatibleDC(pDC);
	CBitmap* now0 = dc0.SelectObject(&title);
	TransparentBlt(pDC->m_hDC, 250, 0, 703, 266, dc0.m_hDC, 0, 0, 703, 266, RGB(255, 255, 255));
	dc0.SelectObject(now0);
	pDC->BitBlt(250, 0, 703, 266, &dc0, 0, 0, SRCCOPY);

	CDC dc1;
	dc1.CreateCompatibleDC(pDC);
	CBitmap* now1 = dc1.SelectObject(&button[0]);
	TransparentBlt(pDC->m_hDC, hpbutton_pos[0], hpbutton_pos[1], 360, 300, dc1.m_hDC, 0, 0, 360, 300, RGB(255, 255, 255));
	dc1.SelectObject(now1);
	pDC->BitBlt(hpbutton_pos[0], hpbutton_pos[1], 360, 300, &dc1, 0, 0, SRCCOPY);

	CDC dc2;
	dc2.CreateCompatibleDC(pDC);
	CBitmap* now2 = dc2.SelectObject(&button[1]);
	TransparentBlt(pDC->m_hDC, hpbutton_pos[0], hpbutton_pos[1]+hpbutton_seperation, 360, 300, dc2.m_hDC, 0, 0, 360, 300, RGB(255, 255, 255));
	dc2.SelectObject(now2);
	pDC->BitBlt(hpbutton_pos[0], hpbutton_pos[1] + hpbutton_seperation, 360, 300, &dc2, 0, 0, SRCCOPY);

	CDC dc3;
	dc3.CreateCompatibleDC(pDC);
	CBitmap* now3 = dc3.SelectObject(&button[2]);
	TransparentBlt(pDC->m_hDC, hpbutton_pos[0], hpbutton_pos[1] + hpbutton_seperation * 2, 360, 300, dc3.m_hDC, 0, 0, 360, 300, RGB(255, 255, 255));
	dc3.SelectObject(now3);
	pDC->BitBlt(hpbutton_pos[0], hpbutton_pos[1] + hpbutton_seperation * 2, 360, 300, &dc3, 0, 0, SRCCOPY);

	CDC dc4;
	dc4.CreateCompatibleDC(pDC);
	CBitmap* now4 = dc4.SelectObject(&button[3]);
	TransparentBlt(pDC->m_hDC, hpbutton_pos[0], hpbutton_pos[1] + hpbutton_seperation * 3, 360, 300, dc4.m_hDC, 0, 0, 360, 300, RGB(255, 255, 255));
	dc4.SelectObject(now4);
	pDC->BitBlt(hpbutton_pos[0], hpbutton_pos[1] + hpbutton_seperation * 3, 360, 300, &dc4, 0, 0, SRCCOPY);
	
}