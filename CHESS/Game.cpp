#include"pch.h"
#include"Game.h"
#include"Resource.h"

void CGame::Init()
{
	map.LoadBitmap(IDB_MAP);
	rank.LoadBitmap(IDB_RANK);
	ranktitle.LoadBitmap(IDB_RANKTITLE);
	setting.LoadBitmap(IDB_SETTING);
	for (int i = 0; i < 4; i++) {
		gplane[i].LoadBitmap(IDB_GREENPLANE);
		rplane[i].LoadBitmap(IDB_REDPLANE);
		bplane[i].LoadBitmap(IDB_BLUEPLANE);
		yplane[i].LoadBitmap(IDB_YELLOWPLANE);
	}
	player[GREEN].temp_plane.LoadBitmap(IDB_GREENPLANE);
	player[RED].temp_plane.LoadBitmap(IDB_REDPLANE);
	player[BLUE].temp_plane.LoadBitmap(IDB_BLUEPLANE);
	player[YELLOW].temp_plane.LoadBitmap(IDB_YELLOWPLANE);

	for (int j = 0; j < 4; j++)
		for (int i = 0; i < 4; i++) {
			player[j].plane_pos[i][0] = airport_pos[j][i][0];
			player[j].plane_pos[i][1] = airport_pos[j][i][1];
			player[j].plane_block_num[i] = 0;
			player[j].plane_state[i] = AIRPORT;
			player[j].finished_plane_num = 0;
		}


	now_player = 0;
	game_over_flag = 0;
	memset(judge_park, 0, sizeof judge_park);
	playing_state = BEFOREDICE;
	exe_state = HOMEPAGE;

	rank_num = 0;
	memset(rank_player, 0, sizeof rank_player);
	for (int i = 0; i < 4; i++)
		player_rank[i] = -1;

}

void CGame::InitDraw()
{
	for (int j = 0; j < 4; j++)
		for (int i = 0; i < 4; i++) {
			player[j].plane_pos[i][0] = airport_pos[j][i][0];
			player[j].plane_pos[i][1] = airport_pos[j][i][1];
			player[j].plane_block_num[i] = 0;
			player[j].plane_state[i] = AIRPORT;
			player[j].finished_plane_num = 0;
		}


	now_player = 0;
	game_over_flag = 0;
	memset(judge_park, 0, sizeof judge_park);
	playing_state = BEFOREDICE;
	exe_state = HOMEPAGE;

	rank_num = 0;
	memset(rank_player, 0, sizeof rank_player);
	for (int i = 0; i < 4; i++)
		player_rank[i] = -1;

	exe_state = HOMEPAGE;
	dice.Init();
	ai.Init();
	game_Bomb.Init();
	//debug
	//for (int i = 0; i < 4; i++)for (int j = 0; j < 4; j++){player[j].plane_block_num[i] = begin_block_num[j] + 46 + i;player[j].plane_state[i] = FLYING;}
}
void CGame::Draw(CDC* pDC)
{

	CDC dc;
	dc.CreateCompatibleDC(pDC);
	CFont font;
	font.CreateFont(30,                                          //   nHeight   
		0,                                                   //   nWidth   
		0,                                                   //   nEscapement 
		0,                                                   //   nOrientation   
		FW_NORMAL,                                   //   nWeight   
		FALSE,                                           //   bItalic   
		FALSE,                                           //   bUnderline   
		0,                                                   //   cStrikeOut   
		ANSI_CHARSET,                             //   nCharSet   
		OUT_DEFAULT_PRECIS,                 //   nOutPrecision   
		CLIP_DEFAULT_PRECIS,               //   nClipPrecision   
		DEFAULT_QUALITY,                       //   nQuality   
		DEFAULT_PITCH | FF_SWISS,     //   nPitchAndFamily     
		_T("楷体"));



	CFont* pOldFont = pDC->SelectObject(&font);
	pDC->SelectObject(&font);
	if (ai.on[now_player])
	{
		//pDC->TextOutW(700, 200, TEXT("点击旋转骰子"));
	}
	else
	{
		if (playing_state == ONDICE)
		{
			pDC->TextOutW(700, 200, TEXT("点击停止骰子"));
		}
		else if (playing_state == BEFOREDICE)
		{
			pDC->TextOutW(700, 200, TEXT("点击旋转骰子"));
		}
		else 
		{
			pDC->TextOutW(700, 200, TEXT("点击飞机飞行"));
		}
	}
	pDC->SelectObject(&pOldFont);
	
	if (playing_state == BEFOREDICE)//画摇前的立体骰子
	{
		dc.SelectObject(&dice.bmp_dices);
		pDC->BitBlt(dice_pos[0], dice_pos[1], 180, 140, &dc, 0, 0, SRCCOPY);
	}
	else//画其他情况的平面骰子
	{
		dc.SelectObject(&dice.bmp_dice[dice.num]);
		pDC->BitBlt(dice_pos[0], dice_pos[1], dice_width, dice_height, &dc, 0, 0, SRCCOPY);
	}

	//画排行榜
	dc.SelectObject(&rank);
	pDC->BitBlt(rank_pos[0], rank_pos[1], 300, 800, &dc, 0, 0, SRCCOPY);
	dc.SelectObject(&ranktitle);
	pDC->BitBlt(rank_pos[0]+110, rank_pos[1]-90, 300, 800, &dc, 0, 0, SRCCOPY);

	//画地图
	dc.SelectObject(&map);
	pDC->BitBlt(0, 0, 800, 800, &dc, 0, 0, SRCCOPY);

	//restart button
	dc.SelectObject(&setting);
	pDC->BitBlt(setting_button_pos[0], setting_button_pos[1], setting_width, setting_height, &dc, 0, 0, SRCCOPY);

	//画摇骰子时旁边的颜色小飞机
	dc.SelectObject(&player[now_player].temp_plane);
	pDC->BitBlt(dice_pos[0] + dice_width / 2 + 17, dice_pos[1] + 150, 45, 45, &dc, 0, 0, SRCCOPY);


	//画16架小飞机
	for (int j = 0; j < 4; j++)
		for (int i = 0; i < 4; i++) {
			dc.SelectObject(&player[j].plane[i]);
			pDC->BitBlt(player[j].plane_pos[i][0], player[j].plane_pos[i][1], 45, 45, &dc, 0, 0, SRCCOPY);
		}
	//画ai选项
	ai.DrawCtrl(pDC);
	ai.DrawLogo(pDC);




	//画Bomb
	//game_Bomb.bomb_block_num = 28;
	if (game_Bomb.bomb_block_num != -1)
	{
		game_Bomb.DrawBomb(pDC);
	}

}

void CGame::Restart(CDC *pDC)
{
	//上一轮的游戏数据全部清零
	srand(time(0));
	InitDraw();
	Draw(pDC);
}
void CGame::NewBomb()
{
	srand(time(0));
	int i = rand() % 52;
	game_Bomb.bomb_block_num = i;
	game_Bomb.bomb_pos[0] = map_pos[i][0];
	game_Bomb.bomb_pos[1] = map_pos[i][1];
}
void CGame::DrawBackGround(CDC* pDC)
{

	CBrush brush((COLORREF)0x00FFFFFF);
	CBrush* pOldBrush = pDC->SelectObject(&brush);
	pDC->Rectangle(0, 0, 1600, 900);
	pDC->SelectObject(pOldBrush);

}