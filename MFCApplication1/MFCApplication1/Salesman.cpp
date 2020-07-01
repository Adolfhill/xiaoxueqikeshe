// Salesman.cpp: 实现文件
//

#include "pch.h"
#include "MFCApplication1.h"
#include "Salesman.h"
#include "afxdialogex.h"


// Salesman 对话框

IMPLEMENT_DYNAMIC(Salesman, CDialogEx)

Salesman::Salesman(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_Salesman, pParent)
{

}

Salesman::~Salesman()
{
}

void Salesman::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Salesman, CDialogEx)
END_MESSAGE_MAP()


// Salesman 消息处理程序
