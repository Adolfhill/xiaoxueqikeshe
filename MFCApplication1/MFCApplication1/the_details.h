#pragma once


// the_details 对话框

class the_details : public CDialogEx
{
	DECLARE_DYNAMIC(the_details)

public:
	the_details(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~the_details();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_the_details };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_list;

private:
	void set_list();
public:
	CString ID;
	virtual BOOL OnInitDialog();
};
