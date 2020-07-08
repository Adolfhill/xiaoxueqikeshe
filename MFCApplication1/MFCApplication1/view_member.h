#pragma once


// view_member 对话框

class view_member : public CDialogEx
{
	DECLARE_DYNAMIC(view_member)

public:
	view_member(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~view_member();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_view_member };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_list;
	virtual BOOL OnInitDialog();

private:
	void set_list();
public:
	afx_msg void OnBnClickedButton1();
};
