#pragma once


// DigGaneOver 对话框

class DigGaneOver : public CDialogEx
{
	DECLARE_DYNAMIC(DigGaneOver)

public:
	bool flag = false;
public:
	DigGaneOver(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~DigGaneOver();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_gameover };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString Result;
	CButton Restart;
	afx_msg void OnBnClickedButtonrestart();
	CString result2;
	CString result3;
};
