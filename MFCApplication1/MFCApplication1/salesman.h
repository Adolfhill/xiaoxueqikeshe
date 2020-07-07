#pragma once
#include <map>
#include <vector>
#include"member_registered.h"
// salesman 对话框




class salesman : public CDialogEx
{
	DECLARE_DYNAMIC(salesman)

public:
	salesman(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~salesman();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_salesman };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClose();
	virtual BOOL OnInitDialog();
private:
	std::map<CString, float> commodity_map;
	std::map<CString, float> get_the_map();     //构建commodity_map
	member member_now;
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	CEdit m_edit_mid;
	CEdit m_edit_mter;
	afx_msg void OnBnClickedButtonmembersignout();
	CEdit m_edit_mid_input;
	CEdit m_edit_mpwd_input;
	CListCtrl m_list;
	CEdit m_edit_commodity_id;
	CEdit m_edit_commodity_count;
	afx_msg void OnBnClickedButtonaddtolist();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButtonselectall();
	afx_msg void OnBnClickedButtonrev();
	afx_msg void OnBnClickedButtondel();

private:
	void Update_member(float sum);
	void Update_stock(CString stock_id,CString stock_count);
	void Update_order_info(CString member_id, int integral);
	CString get_max_order_id();
	void record_details(CString the_id_now, CString stock_id, CString stock_count);
};


