// pay.cpp: 实现文件
//

#include "pch.h"
#include "MFCApplication1.h"
#include "pay.h"
#include "afxdialogex.h"


// pay 对话框

IMPLEMENT_DYNAMIC(pay, CDialogEx)

pay::pay(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_pay, pParent)
{

}

pay::~pay()
{
}

void pay::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_edit_sum);
	DDX_Control(pDX, IDC_EDIT2, m_edit_co);
	DDX_Control(pDX, IDC_EDIT3, m_edit_max_co);
}


BEGIN_MESSAGE_MAP(pay, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_ok, &pay::OnBnClickedButtonok)
	ON_BN_CLICKED(IDC_BUTTON_no, &pay::OnBnClickedButtonno)
	ON_BN_CLICKED(IDC_BUTTON3, &pay::OnBnClickedButton3)
END_MESSAGE_MAP()


// pay 消息处理程序


BOOL pay::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	//显示总价
	CString strSum;
	strSum.Format(_T("%.2lf"), pay::sum);
	m_edit_sum.SetWindowText(strSum);
	//显示积分
	strSum.Format(_T("%.2lf"), integral);
	m_edit_co.SetWindowText(strSum);
	//显示最大可用积分
	if (integral / 100 > sum)
		the_max = sum * 100;
	else
		the_max = int(integral);
	strSum.Format(_T("%.2lf"), the_max);
	m_edit_max_co.SetWindowText(strSum);

	use_integral = 0;
	ok = 0;
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void pay::OnBnClickedButtonok()
{
	// TODO: 在此添加控件通知处理程序代码
	ok = 1;
	CString the_use;
	GetDlgItemText(IDC_EDIT4, the_use);
	int int_the_use = _ttoi(the_use);
	if (float(int_the_use) > the_max&&abs(float(int_the_use) - the_max) > 0.001)
	{
		AfxMessageBox(_T("不能超过最大积分！"));
		return;
	}
	use_integral = int_the_use;
	sum = sum - float(int_the_use) / 100;
	this->OnClose();
	this->OnCancel();
	this->OnDestroy();
	this->PostNcDestroy();
}


void pay::OnBnClickedButtonno()
{
	// TODO: 在此添加控件通知处理程序代码
	ok = 0;
	this->OnClose();
	this->OnCancel();
	this->OnDestroy();
	this->PostNcDestroy();
}


void pay::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	CString the_use;
	GetDlgItemText(IDC_EDIT4, the_use);
	int int_the_use = _ttoi(the_use);
	if (float(int_the_use) > the_max&&abs(float(int_the_use) - the_max) > 0.001)
	{
		AfxMessageBox(_T("不能超过最大积分！"));
		return;
	}
	float sum_now = sum - float(int_the_use) / 100;
	CString str_sum_now;
	str_sum_now.Format(_T("%.2lf"), sum_now);
	AfxMessageBox(_T("共消费") + str_sum_now + _T("元"));
}
