// Manager.cpp: 实现文件
//

#include "pch.h"
#include "MFCApplication1.h"
#include "Manager.h"
#include "afxdialogex.h"
#include "Update_salesman.h"
#include "stock.h"



// Manager 对话框

IMPLEMENT_DYNAMIC(Manager, CDialogEx)

Manager::Manager(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_manager, pParent)
{

}

Manager::~Manager()
{
}

void Manager::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Manager, CDialogEx)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_update_salesman, &Manager::OnBnClickedButtonupdatesalesman)
	ON_BN_CLICKED(IDC_BUTTON1, &Manager::OnBnClickedButton1)
END_MESSAGE_MAP()


// Manager 消息处理程序


BOOL Manager::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void Manager::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CDialog* p = (CDialog*)AfxGetMainWnd();
	p->DestroyWindow();
	CDialogEx::OnClose();
}


void Manager::OnBnClickedButtonupdatesalesman()
{
	// TODO: 在此添加控件通知处理程序代码
	Update_salesman dlg;
	dlg.DoModal();
}


void Manager::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	stock dlg;
	dlg.DoModal();
}
