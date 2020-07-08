#pragma once


// stock 对话框

class stock : public CDialogEx
{
	DECLARE_DYNAMIC(stock)

public:
	stock(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~stock();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_stock };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl m_list;

private:
	void set_list();
	void del_that(CString id);
public:
	afx_msg void OnBnClickedButtonadd();
	afx_msg void OnBnClickedButtondel();
	afx_msg void OnBnClickedButtonapdstock();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
};
