#pragma once


// Salesman 对话框

class Salesman : public CDialogEx
{
	DECLARE_DYNAMIC(Salesman)

public:
	Salesman(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Salesman();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_Salesman };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
