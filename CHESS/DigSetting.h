#pragma once

#include"Game.h"
// DigSetting 对话框

class DigSetting : public CDialogEx
{
	DECLARE_DYNAMIC(DigSetting)
public:
	bool flag = false;
public:
	DigSetting(CWnd* pParent = nullptr); // 标准构造函数

	virtual ~DigSetting();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_Setting };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonexitgame();
	afx_msg void OnBnClickedButtonclosesetting();
	afx_msg void OnBnClickedButtonrestart();
	afx_msg void OnBnClickedCheck1();
	BOOL music;
};
