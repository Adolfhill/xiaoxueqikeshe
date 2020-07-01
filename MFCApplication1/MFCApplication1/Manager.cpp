// Manager.cpp: 实现文件
//

#include "pch.h"
#include "MFCApplication1.h"
#include "Manager.h"
#include "afxdialogex.h"


// Manager 对话框

IMPLEMENT_DYNAMIC(Manager, CDialogEx)

Manager::Manager(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_Manager, pParent)
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
END_MESSAGE_MAP()


// Manager 消息处理程序
