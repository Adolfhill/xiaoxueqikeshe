#pragma once


// pay 对话框

class pay : public CDialogEx
{
	DECLARE_DYNAMIC(pay)

public:
	pay(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~pay();

	float sum;
	float integral;
	//实际使用的积分，100积分抵一块钱，1积分抵1分钱，所以小数部分没意义了
	int use_integral;
	bool ok;
	
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_pay };
#endif

private:
	float the_max;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CEdit m_edit_sum;
	CEdit m_edit_co;
	CEdit m_edit_max_co;
	afx_msg void OnBnClickedButtonok();
	afx_msg void OnBnClickedButtonno();
	afx_msg void OnBnClickedButton3();
};
