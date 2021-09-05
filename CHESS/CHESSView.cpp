
// CHESSView.cpp: CCHESSView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "CHESS.h"
#endif

#include<iostream>

#include "CHESSDoc.h"
#include "CHESSView.h"
using namespace std;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCHESSView

IMPLEMENT_DYNCREATE(CCHESSView, CView)

BEGIN_MESSAGE_MAP(CCHESSView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_TIMER()
	ON_WM_PAINT()
END_MESSAGE_MAP()

// CCHESSView 构造/析构

CCHESSView::CCHESSView() noexcept
{
	// TODO: 在此处添加构造代码

}

CCHESSView::~CCHESSView()
{
}

BOOL CCHESSView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式
	game.Init();
	game.InitDraw(); 
	
	return CView::PreCreateWindow(cs);
}

// CCHESSView 绘图

void CCHESSView::Draw(CDC* pDC)
{

	if (game.exe_state == PLAYING)game.Draw(pDC);
	else if (game.exe_state == HOMEPAGE)homepage.Draw(pDC);

}
void CCHESSView::OnDraw(CDC* pDC)
{
	CCHESSDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	// TODO: 在此处为本机数据添加绘制代码
	Draw(pDC);
}

// CCHESSView 打印

BOOL CCHESSView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CCHESSView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CCHESSView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CCHESSView 诊断

#ifdef _DEBUG
void CCHESSView::AssertValid() const
{
	CView::AssertValid();
}

void CCHESSView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCHESSDoc* CCHESSView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCHESSDoc)));
	return (CCHESSDoc*)m_pDocument;
}
#endif //_DEBUG

// CCHESSView 消息处理程序

void CCHESSView::PLAYINGButtonDown(CPoint point, CDC* pDC)
{
	//如果点中切换AI
	UpdateAIChange(point);
	UpdateRestartButton(point);
	//如果点中骰子
	if (point.x >= dice_pos[0] + 40 && point.x <= dice_pos[0] + 180 && point.y >= dice_pos[1] && point.y <= dice_pos[1] + 140)
	{
		//game.Restart(pDC);
		ShakeDice();
	}
	//点完骰子
	if (game.playing_state == AFTERDICE) {
		UpdatePlayerChange();
		UpdateClickPlane(point);
	}
	Sleep(500);
	Invalidate();
}

void CCHESSView::HOMEPAGEButtonDown(CPoint point, CDC* pDC)
{
	for (int i = 0; i < 4; i++)
	{
		if (point.x >= hpbutton_pos[0] + hpbutton_leftdist[0] && point.x <= hpbutton_pos[0] + hpbutton_rightdist[0] && point.y >= hpbutton_pos[1] + hpbutton_leftdist[1] + hpbutton_seperation * i&&point.y <= hpbutton_pos[1] + hpbutton_rightdist[1] + hpbutton_seperation * i)
		{//如果第i个按键被点到（选择i+1个玩家）
			Sleep(250);
			game.exe_state = PLAYING;//开始游戏
			game.playing_state = BEFOREDICE;//开始游戏
			SetTimer(1, timerAI, NULL);
			game.NewBomb();
			for (int j = i+1; j <= 3; j++)//将ai开关打开
			{
				game.ai.on[j] = true;
			}
			Invalidate();
		}
	}
}
void CCHESSView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CDC* pDC = GetDC();
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (game.exe_state == PLAYING)
		PLAYINGButtonDown(point, pDC);
	else if (game.exe_state == HOMEPAGE)
		HOMEPAGEButtonDown(point, pDC);
	ReleaseDC(pDC);
	CView::OnLButtonDown(nFlags, point);
}
void CCHESSView::UpdateAIChange(CPoint point)
{
	for (int i = 0; i < 4; i++)
	{
		if (point.x >= game.ai.aiCtrl_pos[i][0] && point.x <= game.ai.aiCtrl_pos[i][0] + game.ai.aiCtrl_w && point.y >= game.ai.aiCtrl_pos[i][1] && point.y <= game.ai.aiCtrl_pos[i][1] + game.ai.aiCtrl_h)
		{
			if (game.ai.on[i])
				game.ai.on[i] = false;
			else
			{
				game.ai.on[i] = true;
			}
			//Invalidate();
			OnPaint();
			//RedrawWindow();
			return ;
		}
	}
	return ;
}
void CCHESSView::UpdateRestartButton(CPoint point)
{
	if (point.x >= setting_button_pos[0] && point.x <= setting_button_pos[0] + setting_width && point.y >= setting_button_pos[1] && point.y <= setting_button_pos[1] + setting_height)
	{

		KillTimer(1);
		CDC* pDC = GetDC();
		set.DoModal();
		if (set.flag == 1)
		{
			game.Restart(pDC);
			set.flag = false;
		}
		ReleaseDC(pDC);
		SetTimer(1, timerAI, NULL);
	}
}
void CCHESSView::ShakeDice()
{
	if (game.playing_state == BEFOREDICE) {
		srand(time(0));
		SetTimer(2, timerDice, NULL);
		game.playing_state = ONDICE;
	}
	else if (game.playing_state == ONDICE) {
		KillTimer(2);
		game.playing_state = AFTERDICE;
	}
}
void CCHESSView::UpdatePlayerChange()
{
		//是否换人
		if (game.dice.num != 6) {
			bool next = true;//是否跳转到下一个玩家
			for (int i = 0; i < 4; i++)
				if (game.player[game.now_player].plane_state[i] == AIRPORT2 || game.player[game.now_player].plane_state[i] == FLYING)next = false;
			if (next)
			{
				game.playing_state = BEFOREDICE;
				game.now_player = (game.now_player + 1) % 4;
				while (game.player[game.now_player].finished_plane_num == 4 || game.judge_park[game.now_player])
				{
					game.judge_park[game.now_player] = 0;
					game.now_player = (game.now_player + 1) % 4;
				}
				return;
			}
		}
		else
		{
			if (game.player[game.now_player].finished_plane_num == 4)
			{
				game.now_player = (game.now_player + 1) % 4;
				while (game.player[game.now_player].finished_plane_num == 4 || game.judge_park[game.now_player])
				{
					game.judge_park[game.now_player] = 0;
					game.now_player = (game.now_player + 1) % 4;
				}
				return;
			}
		}
}
void CCHESSView::UpdateClickPlane(CPoint point)
{
	for (int i = 0; i < 4; i++)
	{//查看是否点击四架飞机
		if (point.x >= game.player[game.now_player].plane_pos[i][0] && point.x <= game.player[game.now_player].plane_pos[i][0] + 32 && point.y >= game.player[game.now_player].plane_pos[i][1] && point.y <= game.player[game.now_player].plane_pos[i][1] + 32)
		{
			if (game.dice.num == 6 || game.player[game.now_player].plane_state[i] == AIRPORT2|| game.player[game.now_player].plane_state[i] == FLYING)
			{
				Move(game.now_player, i, game.dice.num,0);
				//f.of << game.now_player << "   " << i << "   " << game.dice.num << "\n";
			}
			else break;//存在已飞的飞机则重新点击
			game.playing_state = BEFOREDICE;
			if (game.dice.num != 6) {//如果不掷6，则轮到下一个人
				game.now_player = (game.now_player + 1) % 4;
				while (game.player[game.now_player].finished_plane_num == 4 || game.judge_park[game.now_player])
				{
					game.judge_park[game.now_player] = 0;
					game.now_player = (game.now_player + 1) % 4;
				}
			}
			break;
		}
	}
}
void CCHESSView::OnTimer(UINT_PTR nIDEvent)
{
	CDC *pDC = GetDC();
	if (nIDEvent == 1)
	{
		if (game.ai.on[game.now_player]&&!game.ai.enterFlag)
		{
			AIAction();
		}
	}
	if (nIDEvent == 2)//摇骰子
	{
		int temp = rand() % 6 + 1;
		CDC dc;
		game.dice.num = temp;
		//Invalidate();
		OnPaint();
		//RedrawWindow();
	}
	ReleaseDC(pDC);
	CView::OnTimer(nIDEvent);
}
void CCHESSView::CheckBump(int player_num,int block_num)
{
	for (int i = 0; i < 4; i++) {//撞回其他飞机 
		if (i == player_num)continue;//自己不能撞回自己的飞机
		for (int j = 0; j < 4; j++)
		{
			if (game.player[i].plane_state[j] != FLYING||game.player[i].plane_block_num[j]>=end_block_num[i]+1||game.player[i].plane_block_num[j]<=begin_block_num[i])continue;
			if (block_num % 52 == game.player[i].plane_block_num[j] % 52) {
				game.player[i].plane_block_num[j] = 0;
				game.player[i].plane_state[j] = AIRPORT;
				MoveAnimation(i, j, airport_pos[i][j][0], airport_pos[i][j][1],0);
			}

		}
			
	}
}

void CCHESSView::CheckPark(int player_num, int plane_num, int block_num)
{
	for (int i = 0; i < 4; i++)//循环parking lot
	{
		if (i == player_num)continue;
		if (game.player[player_num].plane_state[plane_num] != FLYING || block_num >= end_block_num[player_num] + 1 || block_num <= begin_block_num[player_num])
			continue;
		if (block_num % 52 == parking_pos[i])
		{
			game.judge_park[player_num] = 1;
		}
	}
	return;
}

void CCHESSView::CheckBomb(int player_num, int plane_num)
{
	if (game.player[player_num].plane_state[plane_num] != FLYING || game.player[player_num].plane_block_num[plane_num] >= end_block_num[player_num] + 1 || game.player[player_num].plane_block_num[plane_num] <= begin_block_num[player_num])
		return;
	if (game.player[player_num].plane_block_num[plane_num] % 52 == game.game_Bomb.bomb_block_num)
	{
		CDC* pDC = GetDC();
		game.game_Bomb.BombAnimation(pDC);
		game.player[player_num].plane_block_num[plane_num] = 0;
		game.player[player_num].plane_state[plane_num] = AIRPORT;
		MoveAnimation(player_num, plane_num, airport_pos[player_num][plane_num][0], airport_pos[player_num][plane_num][1],0);
		game.NewBomb();
		OnPaint();
		//RedrawWindow();
		ReleaseDC(pDC);
	}
	
}

void CCHESSView::CheckSpecialJump(int player_num, int plane_num)
{
	if (game.player[player_num].plane_block_num[plane_num] == express_block_num[player_num])
	{
		Move(player_num, plane_num, 12, 1);//如果跳到快捷通道，前进12格
		return;
	}
	else if (game.player[player_num].plane_block_num[plane_num] % 4 == mod_jump[player_num])
	{
		Move(player_num, plane_num, 4, 1);//如果跳到同色格子，前进4格
		return;
	}
	for (int i = 0; i < 8; i++)
	{
		if (game.player[player_num].plane_block_num[plane_num] == plus_block_num[i] && player_num != i % 4)
		{
			Move(player_num, plane_num, 2, 1);//如果跳到+2格子，前进2格
			return;
		}
	}
	for (int i = 0; i < 8; i++)
	{
		if (game.player[player_num].plane_block_num[plane_num] == minus_block_num[i] && player_num != i % 4)
		{
			Move(player_num, plane_num, -1, 1);//如果跳到-1格子，后退1格
			return;
		}
	}
}
//移动飞机
void CCHESSView::Move(int player_num, int plane_num,int jump_num, bool double_jump_or_not)
{
	
	if (game.player[player_num].plane_state[plane_num] == AIRPORT && jump_num == 6) {
		game.player[player_num].plane_state[plane_num] = AIRPORT2;
		game.player[player_num].plane_block_num[plane_num] = begin_block_num[player_num];
		MoveAnimation(player_num, plane_num, airport_pos2[player_num][0], airport_pos2[player_num][1],0);
	}
	else if (game.player[player_num].plane_state[plane_num] == AIRPORT2)
	{
		game.player[player_num].plane_state[plane_num] = FLYING;
		int temp = game.player[player_num].plane_block_num[plane_num] + jump_num;
		game.player[player_num].plane_block_num[plane_num] = temp;
		MoveAnimation(player_num, plane_num, map_pos[temp][0], map_pos[temp][1],0);
		CheckBomb(player_num,plane_num);
		CheckBump(player_num,temp);
		CheckPark(player_num, plane_num, temp);
		if(!double_jump_or_not)CheckSpecialJump(player_num, plane_num);
	}
	else if (game.player[player_num].plane_state[plane_num] == FLYING)
	{
		int temp = game.player[player_num].plane_block_num[plane_num] + jump_num;
		game.player[player_num].plane_block_num[plane_num] = temp;
		if (temp <= end_block_num[player_num])//如果还没进入降落轨道
		{
			MoveAnimation(player_num, plane_num, map_pos[temp][0], map_pos[temp][1],0);
			CheckBomb(player_num, plane_num);
			CheckBump(player_num, temp);
			CheckPark(player_num, plane_num, temp);
			if (!double_jump_or_not)CheckSpecialJump(player_num, plane_num);
		}
			
		else if (temp < finish_block_num[player_num])//开始进入降落轨道，但不反弹
			MoveAnimation(player_num, plane_num, airport_pos3[player_num][temp - end_block_num[player_num]-1][0], airport_pos3[player_num][temp - end_block_num[player_num]-1][1],0);
		else if (temp == finish_block_num[player_num])//直接抵达终点
		{
			game.player[player_num].plane_state[plane_num] = FINISHED;
			game.player[player_num].finished_plane_num++;
			MoveAnimation(player_num, plane_num, airport_pos3[player_num][temp - end_block_num[player_num]-1][0], airport_pos3[player_num][temp - end_block_num[player_num]-1][1],0);
			Sleep(500);
			FinishOperation(player_num, plane_num);
		}
		else if (temp > finish_block_num[player_num])//反弹
		{
			temp = end_block_num[player_num] + 12 - (temp - end_block_num[player_num]);
			game.player[player_num].plane_block_num[plane_num] = temp;

			MoveAnimation(player_num, plane_num, airport_pos3[player_num][temp - end_block_num[player_num]-1][0], airport_pos3[player_num][temp - end_block_num[player_num]-1][1],0);
			if (temp==end_block_num[player_num]+1)//可能撞回其他飞机
			{
				CheckBump(player_num, temp);
			}
		}
		
	}
}
//输入终止坐标，自动绘制从起始点到终止点的动画
void CCHESSView::MoveAnimation(int player_num, int plane_num, int endx, int endy,bool flag)
{
	CDC* pDC = GetDC();
	int startx = game.player[player_num].plane_pos[plane_num][0];
	int starty = game.player[player_num].plane_pos[plane_num][1];
	int speedx = (endx - startx) / 10, speedy = (endy - starty) / 10;	
	int xx = startx - speedx, yy = starty - speedy;
	int flagx = startx <= endx ? 1 : -1, flagy = starty <= endy ? 1 : -1;
	while (speedx != 0 && speedy != 0)
	{
		xx += speedx, yy += speedy;
		if (flagx*xx > flagx*endx || flagy * yy > flagy*endy)break;
		game.player[player_num].plane_pos[plane_num][0] = xx;
		game.player[player_num].plane_pos[plane_num][1] = yy;
		Sleep(30);
		//Invalidate();
		if (flag)game.DrawBackGround(pDC);
		OnPaint();
		//RedrawWindow();
	}
	while (speedy != 0)
	{
		yy += speedy;
		if (flagy * yy > flagy * endy)break;
		//game.player[player_num].plane_pos[plane_num][0] = xx;
		game.player[player_num].plane_pos[plane_num][1] = yy;
		Sleep(30);
		//Invalidate();
		if (flag)game.DrawBackGround(pDC);
		OnPaint();
		//RedrawWindow();
	}
	while (speedx != 0 )
	{
		xx += speedx;
		if (flagx * xx > flagx * endx)break;
		game.player[player_num].plane_pos[plane_num][0] = xx;
		//game.player[player_num].plane_pos[plane_num][1] = yy;
		Sleep(30);
		//Invalidate();
		if (flag)game.DrawBackGround(pDC);
		OnPaint();
		//RedrawWindow();
	}
	game.player[player_num].plane_pos[plane_num][0] = endx;
	game.player[player_num].plane_pos[plane_num][1] = endy;
	Sleep(30);
	//Invalidate();
	if (flag)game.DrawBackGround(pDC);
	OnPaint();
	//RedrawWindow();
	ReleaseDC(pDC);
}

void CCHESSView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
	CDC *pDC = GetDC();
	Draw(pDC);
	ReleaseDC(pDC);

	// 不为绘图消息调用 CView::OnPaint()
}
void CCHESSView::AIAction()
{
	if (game.judge_park[game.now_player])return;
	if (game.player[game.now_player].finished_plane_num == 4)return;

	//ai先要掷色子
	if (game.playing_state == BEFOREDICE)
	{
		srand(time(0));
		game.playing_state = ONDICE;
		int i=0;
		int dice_frequency = 10;
		while(i<=dice_frequency)
		{
			int temp = rand() % 6 + 1;
			CDC dc;
			game.dice.num = temp;
			OnPaint();
			//Invalidate();
			//RedrawWindow();
			Sleep(timerDice);
			i++;
		}
		game.playing_state = AFTERDICE;
	}
	if (game.playing_state == ONDICE)
	{
		srand(time(0));
		int i = 0;
		KillTimer(2);
		while (i <= 15)
		{
			int temp = rand() % 6 + 1;
			CDC dc;
			game.dice.num = temp;
			OnPaint();
			//Invalidate();
			//RedrawWindow();
			Sleep(timerDice);
			i++;
		}
		game.playing_state = AFTERDICE;
	}
	
	UpdatePlayerChange();//查看掷出的点数能不能走子，不能跳转下一个玩家
	if (game.playing_state == BEFOREDICE)
	{
		Sleep(1500);//如果改变了玩家，则停留一段骰子点数后退出
		//Invalidate();
		OnPaint();
		//RedrawWindow();
		return;
	}
	else//如果没改变玩家，则走子
	{
		AIMovePlane();
		Sleep(1500);
		if (game.dice.num != 6)
		{
			game.now_player = (game.now_player + 1) % 4;
			while (game.player[game.now_player].finished_plane_num == 4 || game.judge_park[game.now_player])
			{
				game.judge_park[game.now_player] = 0;
				game.now_player = (game.now_player + 1) % 4;
			}
		}
		game.playing_state = BEFOREDICE;
		OnPaint();
	}
}
void CCHESSView::AIMovePlane()
{

	vector<int> available;//可走的棋子
	if (game.dice.num != 6) {
		for (int i = 0; i < 4; i++)//将可走的棋子加入vector
			if (game.player[game.now_player].plane_state[i] == AIRPORT2 || game.player[game.now_player].plane_state[i] == FLYING)
			{
				available.push_back(i);//available的size不为0
			}
				
	}
	else {//点数为6则均可走
		for (int i = 0; i < 4; i++)//将可走的棋子加入vector
		{
			if (game.player[game.now_player].plane_state[i] == FINISHED)
				continue;
			available.push_back(i);//available的size不为0
		}
	}

	if (available.size() == 0)return;


	//策略1：先判断能不能撞飞其他飞机
	for (int i = 0; i < available.size(); i++) {//枚举可行棋子
		if (game.player[game.now_player].plane_state[available[i]] == AIRPORT)continue;
		for (int j = 0; j < 4; j++) {//循环四个玩家j
				if (j == game.now_player)continue;//j不为当前玩家
				for (int k = 0; k < 4; k++) {//循环四个棋子				
					if (game.player[j].plane_block_num[k] >= end_block_num[j] + 2 || game.player[j].plane_state[k] != FLYING)continue;//如果玩家j棋子k不能被撞，则continue
					if (game.player[j].plane_block_num[k] == game.player[game.now_player].plane_block_num[available[i]] + game.dice.num) {
						Move(game.now_player, available[i], game.dice.num, 0);
						return;
					}
				}
		}
	}

	//策略2：判断能不能起飞
	if (game.dice.num == 6)
		for (int i = 0; i < 4; i++)
			if (game.player[game.now_player].plane_state[i] == AIRPORT) {
				Move(game.now_player, i, game.dice.num, 0);
				return;
			}

	//策略3：判断能不能走快捷通道	
	for (int i = 0; i < available.size(); i++) {//枚举可行棋子
		if (game.player[game.now_player].plane_state[available[i]] == AIRPORT)continue;
		if ((game.player[game.now_player].plane_block_num[available[i]] + game.dice.num)  == express_block_num[game.now_player]) {
			Move(game.now_player, available[i], game.dice.num, 0);
			return;
		}
	}

	//策略4：判断能不能跳跃4格
	for (int i = 0; i < available.size(); i++) {//枚举可行棋子
		if (game.player[game.now_player].plane_state[available[i]] == AIRPORT)continue;
		if ((game.player[game.now_player].plane_block_num[available[i]]+game.dice.num) % 4 == mod_jump[game.now_player]) {
			Move(game.now_player, available[i], game.dice.num, 0);
			return;
		}
	}

	//策略5：判断能不能跳跃2格
	for (int i = 0; i < available.size(); i++) {//枚举可行棋子
		if (game.player[game.now_player].plane_state[available[i]] == AIRPORT)continue;
		for (int j = 0; j < 8; j++) {
			if ((game.player[game.now_player].plane_block_num[available[i]] + game.dice.num) == plus_block_num[j] && game.now_player % 4 != j) {				
				Move(game.now_player, available[i], game.dice.num, 0);
				return;
			}
		}
	}

	//策略6：能不能使得进入最终轨道的棋子达到终点
	for (int i = 0; i < available.size(); i++) {//枚举可行棋子
		if (game.player[game.now_player].plane_state[available[i]] == AIRPORT)continue;
		if ((game.player[game.now_player].plane_block_num[available[i]] + game.dice.num) == finish_block_num[game.now_player]) {
			Move(game.now_player, available[i], game.dice.num, 0);
			return;
		}
	}

	//策略7：判断能不能不-1
	vector<int> available2;//不-1的棋子集合
	for (int i = 0; i < available.size(); i++) {//枚举可行棋子
		if (game.player[game.now_player].plane_state[available[i]] == AIRPORT)continue;
		bool tempflag = false;
		for (int j = 0; j < 8; j++) {
			if ((game.player[game.now_player].plane_block_num[available[i]] + game.dice.num) == minus_block_num[j] && game.now_player % 4 != j) {
				tempflag = true;
			}
		}
		if (tempflag == false)available2.push_back(available[i]);
	}
	srand(time(0));
	if (available2.size() > 0)
	{
		int temp = rand() % available2.size();
		Move(game.now_player, available2[temp], game.dice.num, 0);
		return;
	}

	//策略8：乱走一气
	{
		int temp = rand() % available.size();
		Move(game.now_player, available[temp], game.dice.num, 0);
		return;
	}
}



void CCHESSView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
}
void CCHESSView::FinishOperation(int player_num, int plane_num)
{
	if (game.player_rank[player_num] == -1)//更新ranknum
	{
		game.player_rank[player_num] = game.rank_num;
		game.rank_player[game.rank_num] = player_num;
		game.rank_num++;
	}
	MoveAnimation(player_num, plane_num, ranks_pos[game.player_rank[player_num]][game.player[player_num].finished_plane_num - 1][0], ranks_pos[game.player_rank[player_num]][game.player[player_num].finished_plane_num - 1][1],1);
	UpdateSortRank(player_num);
	CDC* pDC = GetDC();
	game.DrawBackGround(pDC);
	ReleaseDC(pDC);
	OnPaint();
	//RedrawWindow();
	int winner=0;
	for (int i = 0; i < 4; i++)
		if (game.player[i].finished_plane_num == 4)winner++;
	//弹出游戏结束对话框
	if (winner == 3)
	{
		Sleep(2000);
		CString s1,s2,s3;
		switch (game.rank_player[0])
		{
		case GREEN:
			s1.Format(_T("恭喜绿色棋子"));
			break;
		case RED:
			s1.Format(_T("恭喜红色棋子"));
			break;
		case YELLOW:
			s1.Format(_T("恭喜黄色棋子"));
			break;
		case BLUE:
			s1.Format(_T("恭喜蓝色棋子"));
			break;

		}
		s1.Append(_T("取得了第一名!"));
		gameover.Result = s1;
		switch (game.rank_player[1])
		{
		case GREEN:
			s2.Format(_T("恭喜绿色棋子"));
			break;
		case RED:
			s2.Format(_T("恭喜红色棋子"));
			break;
		case YELLOW:
			s2.Format(_T("恭喜黄色棋子"));
			break;
		case BLUE:
			s2.Format(_T("恭喜蓝色棋子"));
			break;

		}
		s2.Append(_T("取得了第二名!"));
		gameover.result2= s2;
		switch (game.rank_player[2])
		{
		case GREEN:
			s3.Format(_T("恭喜绿色棋子"));
			break;
		case RED:
			s3.Format(_T("恭喜红色棋子"));
			break;
		case YELLOW:
			s3.Format(_T("恭喜黄色棋子"));
			break;
		case BLUE:
			s3.Format(_T("恭喜蓝色棋子"));
			break;

		}
		s3.Append(_T("取得了第三名!"));
		gameover.result3 = s3;
		UpdateData(false);
		gameover.DoModal();
		if (gameover.flag)
		{
			CDC* pDC = GetDC();
			game.Restart(pDC);
			gameover.flag = 0;
			ReleaseDC(pDC);
		}
	}
}
void CCHESSView::UpdateSortRank(int player_num)
{

	for (int i = game.player_rank[player_num] - 1; i >= 0; i--)
	{
		int tempplayer = game.rank_player[i];
		if (game.player[tempplayer].finished_plane_num < game.player[player_num].finished_plane_num)
		{
			swap(game.rank_player[i], game.rank_player[game.player_rank[player_num]]);
			swap(game.player_rank[player_num], game.player_rank[tempplayer]);
		}
		else break;
	}
	for (int i = 0; i < 4; i++)
	{
		int cnt = 0;
		for (int j = 0; j < 4; j++)
		{
			if (game.player[i].plane_state[j] != FINISHED)continue;
			game.player[i].plane_pos[j][0] = ranks_pos[game.player_rank[i]][cnt][0];
			game.player[i].plane_pos[j][1] = ranks_pos[game.player_rank[i]][cnt][1];
			cnt++;
		}
	}
}
