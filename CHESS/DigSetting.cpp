// DigSetting.cpp: 实现文件
//

#include "pch.h"
#include "CHESS.h"
#include "DigSetting.h"
#include "afxdialogex.h"
#include<mmsystem.h>
#include<windows.h>
#pragma comment(lib, "WINMM.LIB")

// DigSetting 对话框

IMPLEMENT_DYNAMIC(DigSetting, CDialogEx)

DigSetting::DigSetting(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_Setting, pParent)
	, music(FALSE)
{
	
}

DigSetting::~DigSetting()
{
}

void DigSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK1, music);
}


BEGIN_MESSAGE_MAP(DigSetting, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_exitgame, &DigSetting::OnBnClickedButtonexitgame)
	ON_BN_CLICKED(IDC_BUTTON_close_setting, &DigSetting::OnBnClickedButtonclosesetting)
	ON_BN_CLICKED(IDC_BUTTON_restart, &DigSetting::OnBnClickedButtonrestart)
	ON_BN_CLICKED(IDC_CHECK1, &DigSetting::OnBnClickedCheck1)
END_MESSAGE_MAP()


// DigSetting 消息处理程序


void DigSetting::OnBnClickedButtonexitgame()
{
	// TODO: 在此添加控件通知处理程序代码
	exit(0);
}


void DigSetting::OnBnClickedButtonclosesetting()
{
	// TODO: 在此添加控件通知处理程序代码
	PostMessage(WM_CLOSE);
}


void DigSetting::OnBnClickedButtonrestart()
{
	flag = true;
	PostMessage(WM_CLOSE);
	// TODO: 在此添加控件通知处理程序代码
}


void DigSetting::OnBnClickedCheck1()
{
	// TODO: 在此添加控件通知处理程序代码
	CButton* pBtn = (CButton*)GetDlgItem(IDC_CHECK1);
	int state = pBtn->GetCheck();
	if (state == 1)
	{
		music = true;
		UpdateData(false);
		PlaySound((LPCTSTR)IDR_WAVE1, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC);
	}
	if (state == 0)
	{
		music = false;
		UpdateData(false);
		PlaySound(NULL, NULL, NULL);
	}
	//PostMessage(WM_CLOSE);
}


