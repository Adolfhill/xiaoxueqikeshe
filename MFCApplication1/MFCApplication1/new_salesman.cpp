// new_salesman.cpp: 实现文件
//

#include "pch.h"
#include "MFCApplication1.h"
#include "new_salesman.h"
#include "afxdialogex.h"


// new_salesman 对话框

IMPLEMENT_DYNAMIC(new_salesman, CDialogEx)

new_salesman::new_salesman(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_new_salesman, pParent)
{

}

new_salesman::~new_salesman()
{
}

void new_salesman::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(new_salesman, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &new_salesman::OnBnClickedButton1)
END_MESSAGE_MAP()


// new_salesman 消息处理程序


void new_salesman::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString new_pwd, new_name;
	GetDlgItemText(IDC_EDIT1, new_name);
	GetDlgItemText(IDC_EDIT2, new_pwd);
	if (new_pwd == "")
	{
		AfxMessageBox(_T("密码不能为空！"));
		return;
	}
	if (new_pwd.GetLength() < 6)
	{
		AfxMessageBox(_T("密码应大于六位！"));
		return;
	}
	if (new_name == "")
		new_name = _T("NULL");
	else
		new_name = _T("'") + new_name + _T("'");
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
		strSql.Format(_T("insert into salesman (name,pwd) values("+new_name+","+new_pwd+")"));
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
		