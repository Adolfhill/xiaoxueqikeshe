// apd_the_stock.cpp: 实现文件
//

#include "pch.h"
#include "MFCApplication1.h"
#include "apd_the_stock.h"
#include "afxdialogex.h"


// apd_the_stock 对话框

IMPLEMENT_DYNAMIC(apd_the_stock, CDialogEx)

apd_the_stock::apd_the_stock(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_apd_the_stock, pParent)
{

}

apd_the_stock::~apd_the_stock()
{
}

void apd_the_stock::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_id, m_edit_id);
	DDX_Control(pDX, IDC_EDIT_prise, m_edit_prise);
	DDX_Control(pDX, IDC_EDIT_name, m_edit_name);
	DDX_Control(pDX, IDC_EDIT_stock, m_edit_stock);
}


BEGIN_MESSAGE_MAP(apd_the_stock, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &apd_the_stock::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &apd_the_stock::OnBnClickedButton2)
END_MESSAGE_MAP()


// apd_the_stock 消息处理程序


void apd_the_stock::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItemText(IDC_EDIT_id, id);
	GetDlgItemText(IDC_EDIT_prise, prise);
	GetDlgItemText(IDC_EDIT_name, name);
	GetDlgItemText(IDC_EDIT_stock, stock);
	if (id == "" || prise == "" || name == "" || stock == "")
	{
		AfxMessageBox(_T("各项不能为空！"));
		return;
	}
	end_upd = 0;
	_ConnectionPtr m_pConnection;//数据库连接对象
	_CommandPtr m_pCommand;//数据库命令对象
	HRESULT hresult = m_pConnection.CreateInstance("ADODB.Connection"); //创建Connection对象
	if (SUCCEEDED(hresult))
	{
		m_pCommand.CreateInstance("ADODB.Command");
		CString strConnection("Driver={sql server};server=127.0.0.1;database=MSCSDB;uid=sa;pwd=123456;");
		m_pConnection->Open((LPCTSTR)strConnection, "", "", adModeUnknown);
		CString strSql;
		strSql.Format(_T("update stock set name='%s',prise=%s,stock=%s where id=%s"), name, prise, stock, id);
		m_pCommand->ActiveConnection = m_pConnection;
		m_pCommand->CommandText = (LPCTSTR)strSql;
		m_pCommand->Execute(NULL, NULL, adCmdUnknown);
		m_pCommand = NULL;
		m_pConnection->Close();
		m_pConnection = NULL;

	}
	this->OnClose();
	this->OnCancel();
	this->OnDestroy();
	this->PostNcDestroy();
}


BOOL apd_the_stock::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	m_edit_id.SetWindowText(id);
	m_edit_name.SetWindowText(name);
	m_edit_prise.SetWindowText(prise);
	m_edit_stock.SetWindowText(stock);
	end_upd = 1;

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void apd_the_stock::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	end_upd = 0;
	this->OnClose();
	this->OnCancel();
	this->OnDestroy();
	this->PostNcDestroy();
}
