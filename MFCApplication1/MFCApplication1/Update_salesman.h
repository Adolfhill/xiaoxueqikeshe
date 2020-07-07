#pragma once


// Update_salesman 对话框

class Update_salesman : public CDialogEx
{
	DECLARE_DYNAMIC(Update_salesman)

public:
	Update_salesman(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Update_salesman();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_update_salesman };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_list;
	virtual BOOL OnInitDialog();

private:
	void set_list();
	void del_salesman(CString id);
public:
	afx_msg void OnBnClickedButtonadd();
	afx_msg void OnBnClickedButtondel();
	afx_msg void OnBnClickedButtonupdate();
};
