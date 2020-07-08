#pragma once


// addstock 对话框

class addstock : public CDialogEx
{
	DECLARE_DYNAMIC(addstock)

public:
	addstock(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~addstock();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_add_stock };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
};
