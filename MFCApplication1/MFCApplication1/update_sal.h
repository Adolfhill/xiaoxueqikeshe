#pragma once


// update_sal 对话框

class update_sal : public CDialogEx
{
	DECLARE_DYNAMIC(update_sal)

public:
	update_sal(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~update_sal();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_edit_id;
	CEdit m_edit_pwd;
	CEdit m_edit_name;
	afx_msg void OnBnClickedButton1();
	CString ID, PWD, NAME;

	virtual BOOL OnInitDialog();
};
