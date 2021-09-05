// DigGaneOver.cpp: 实现文件
//

#include "pch.h"
#include "CHESS.h"
#include "DigGameOver.h"
#include "afxdialogex.h"


// DigGaneOver 对话框

IMPLEMENT_DYNAMIC(DigGaneOver, CDialogEx)

DigGaneOver::DigGaneOver(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_gameover, pParent)
	, Result(_T(""))
	, result2(_T(""))
	, result3(_T(""))
{

}

DigGaneOver::~DigGaneOver()
{
}

void DigGaneOver::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_STATIC_result, Result);
	DDX_Control(pDX, IDC_BUTTON_restart, Restart);
	DDX_Text(pDX, IDC_STATIC_result2, result2);
	DDX_Text(pDX, IDC_STATIC_result3, result3);
}


BEGIN_MESSAGE_MAP(DigGaneOver, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_restart, &DigGaneOver::OnBnClickedButtonrestart)
END_MESSAGE_MAP()


// DigGaneOver 消息处理程序


void DigGaneOver::OnBnClickedButtonrestart()
{
	// TODO: 在此添加控件通知处理程序代码
	flag = true;
	PostMessage(WM_CLOSE);
}


