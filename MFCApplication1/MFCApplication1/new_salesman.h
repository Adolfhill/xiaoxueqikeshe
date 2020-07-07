#pragma once


// new_salesman 对话框

class new_salesman : public CDialogEx
{
	DECLARE_DYNAMIC(new_salesman)

public:
	new_salesman(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~new_salesman();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_new_salesman };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
};
