#pragma once


// view_member_details 对话框

class view_member_details : public CDialogEx
{
	DECLARE_DYNAMIC(view_member_details)

public:
	view_member_details(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~view_member_details();
	CString ID;

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_view_details };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_list;

private:
	void set_list();
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton1();
};
