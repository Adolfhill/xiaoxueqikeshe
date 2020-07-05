#pragma once

struct member
{
	CString member_id;
	bool if_login;
	//积分，用于抵现
	float integral;
	//消费，用于打折
	float consumption;
};


// member_registered 对话框

class member_registered : public CDialogEx
{
	DECLARE_DYNAMIC(member_registered)

public:
	member_registered(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~member_registered();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_registered };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	virtual BOOL OnInitDialog();
	member get_the_new_member();
	bool ok;
	member member_now;
	afx_msg void OnBnClickedButton2();
};
