
// CHESSView.h: CCHESSView 类的接口
//CHESSCHESS

#pragma once
#include"Game.h"
#include "CHESSDoc.h"
#include<ctime>
#include<mmsystem.h>
#include<windows.h>
#include<vector>
#include"DigSetting.h"
#include"DigGameOver.h"

class CCHESSView : public CView
{
	
protected: // 仅从序列化创建
	CCHESSView() noexcept;
	DECLARE_DYNCREATE(CCHESSView)

// 特性
public:
	CCHESSDoc* GetDocument() const;
public:
// 操作
public:

// 重写
	
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CCHESSView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()

public:
	DigGaneOver gameover;
	DigSetting set;
	CHomepage homepage;
	CGame game;

public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void CCHESSView::OnTimer(UINT_PTR nIDEvent); 

	void Draw(CDC*);

	void MoveAnimation(int player_num, int plane_num, int endx, int endy,bool flag);
	void Move(int player_num, int plane_num, int jump_num, bool double_jump_or_not);
	void ShakeDice();//摇筛子
	//void AfterDice(CPoint point);//摇完筛子

	void UpdateRestartButton(CPoint point);
	void UpdateAIChange(CPoint point);//判断是否切换AI状态
	void UpdatePlayerChange();
	void UpdateClickPlane(CPoint point);

	void AIAction();//AI的行为
	void AIMovePlane();//AI走子

	void CheckBomb(int player_num,int plane_num);//判断会不会撞上炸弹
	void CheckBump(int player_num,int block_num);//判断会不会撞机
	void CheckSpecialJump(int player_num,int plane_num); 
	void CheckPark(int player_num, int plane_num, int block_num);

	void FinishOperation(int,int);//某棋子走到终点后排名和更新排行榜
	void UpdateSortRank(int);//排行榜排名sort
	
	void PLAYINGButtonDown(CPoint point, CDC* pDC);//exe_state==playing时点击鼠标的操作
	void HOMEPAGEButtonDown(CPoint point, CDC* pDC);//exe_state==playing时点击鼠标的操作
	afx_msg void OnPaint();
	virtual void OnInitialUpdate();
};

#ifndef _DEBUG  // CHESSView.cpp 中的调试版本
inline CCHESSDoc* CCHESSView::GetDocument() const
   { return reinterpret_cast<CCHESSDoc*>(m_pDocument); }
#endif

