#pragma once
#include"pch.h"
#include"data.h"

class CHomepage
{
public:
	CBitmap background;
	CBitmap button[4];
	CBitmap title;
public:
	CHomepage();
	void Draw(CDC *pDC); 
};