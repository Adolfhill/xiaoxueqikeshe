﻿#pragma once


// Manager 对话框

class Manager : public CDialogEx
{
	DECLARE_DYNAMIC(Manager)

public:
	Manager(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Manager();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_manager };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	afx_msg void OnBnClickedButtonupdatesalesman();
	afx_msg void OnBnClickedButton1();
};
