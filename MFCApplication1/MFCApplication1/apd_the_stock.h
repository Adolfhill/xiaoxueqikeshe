#pragma once


// apd_the_stock 对话框

class apd_the_stock : public CDialogEx
{
	DECLARE_DYNAMIC(apd_the_stock)

public:
	apd_the_stock(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~apd_the_stock();
	CString id, prise, stock, name;
	bool end_upd;


// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_apd_the_stock };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	virtual BOOL OnInitDialog();
	CEdit m_edit_id;
	CEdit m_edit_prise;
	CEdit m_edit_name;
	CEdit m_edit_stock;
	afx_msg void OnBnClickedButton2();
};
