// Manager.cpp: 实现文件
//

#include "pch.h"
#include "MFCApplication1.h"
#include "Manager.h"
#include "afxdialogex.h"


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
