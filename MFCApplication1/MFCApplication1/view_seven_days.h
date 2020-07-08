#pragma once


// view_seven_days 对话框

class view_seven_days : public CDialogEx
{
	DECLARE_DYNAMIC(view_seven_days)

public:
	view_seven_days(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~view_seven_days();
	CString ID;

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_7days };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_list;
	virtual BOOL OnInitDialog();

private:
	void set_list();
};
