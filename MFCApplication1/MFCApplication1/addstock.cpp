// addstock.cpp: 实现文件
//

#include "pch.h"
#include "MFCApplication1.h"
#include "addstock.h"
#include "afxdialogex.h"


// addstock 对话框

IMPLEMENT_DYNAMIC(addstock, CDialogEx)

addstock::addstock(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_add_stock, pParent)
{

}

addstock::~addstock()
{
}

void addstock::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(addstock, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &addstock::OnBnClickedButton1)
END_MESSAGE_MAP()


// addstock 消息处理程序


void addstock::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString name, prise, stock;
	GetDlgItemText(IDC_EDIT_name, name);
	GetDlgItemText(IDC_EDIT_prise, prise);
	GetDlgItemText(IDC_EDIT_stock, stock);
	if (name == "" || prise == "" || stock == "")
	{
		AfxMessageBox(_T("各项不能为空！"));
		return;
	}
	_ConnectionPtr m_pConnection;
	_CommandPtr m_pCommand;
	_RecordsetPtr m_pRecordset;
	CString strSql;
	HRESULT hr = m_pConnection.CreateInstance("ADODB.Connection");
	if (SUCCEEDED(hr))
	{
		m_pCommand.CreateInstance("ADODB.Command");
		CString strConnection("Driver={sql server};server=127.0.0.1;database=MSCSDB;uid=sa;pwd=123456;");
		m_pConnection->Open((LPCTSTR)strConnection, "", "", adModeUnknown);
		CString strSql;
		strSql.Format(_T("insert into stock (name,prise,stock) values ('%s',%s,%s)"),name,prise,stock);
		m_pCommand->ActiveConnection = m_pConnection;
		m_pCommand->CommandText = (LPCTSTR)strSql;
		m_pCommand->Execute(NULL, NULL, adCmdUnknown);
		m_pCommand = NULL;
		m_pConnection->Close();
		m_pConnection = NULL;
		ok = 1;
	}
	this->OnClose();
	this->OnCancel();
	this->OnDestroy();
	this->PostNcDestroy();
}


BOOL addstock::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	ok = 0;
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
