// member_registered.cpp: 实现文件
//

#include "pch.h"
#include "MFCApplication1.h"
#include "member_registered.h"
#include "afxdialogex.h"


// member_registered 对话框

IMPLEMENT_DYNAMIC(member_registered, CDialogEx)

member_registered::member_registered(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_registered, pParent)
{

}

member_registered::~member_registered()
{
}

void member_registered::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(member_registered, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &member_registered::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &member_registered::OnBnClickedButton2)
END_MESSAGE_MAP()


// member_registered 消息处理程序


void member_registered::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString new_member_pwd, new_member_name;
	GetDlgItemText(IDC_EDIT_registered_name, new_member_name);
	GetDlgItemText(IDC_EDIT_registered_pwd, new_member_pwd);
	if (new_member_name == "")
		new_member_name = "NULL";
	else
		new_member_name = CString("'") + new_member_name + CString("'");
	if (new_member_pwd == "")
	{
		AfxMessageBox(_T("密码不能为空！"));
		return;
	}
	if (new_member_pwd.GetLength() < 6)
	{
		AfxMessageBox(_T("密码不能少于六位！"));
		return;
	}
	//请求数据库
	_ConnectionPtr m_pConnection;
	_CommandPtr m_pCommand;
	HRESULT hresult = m_pConnection.CreateInstance("ADODB.Connection");
	if (SUCCEEDED(hresult))
	{
		m_pCommand.CreateInstance("ADODB.Command");
		CString strConnection("Driver={sql server};server=127.0.0.1;database=MSCSDB;uid=sa;pwd=123456;");
		m_pConnection->Open((LPCTSTR)strConnection, "", "", adModeUnknown);
		CString strSql;
		strSql.Format(_T("insert into member (member_name,pwd,integral,consumption) values ("+ new_member_name +",'"+  new_member_pwd +"',0,0)"));
		m_pCommand->ActiveConnection = m_pConnection;
		m_pCommand->CommandText = (LPCTSTR)strSql;
		m_pCommand->Execute(NULL, NULL, adCmdUnknown);
		m_pCommand = NULL;
		m_pConnection->Close();
		m_pConnection = NULL;
		ok = 1;
		member_now = get_the_new_member();
	}
	this->OnClose();
	this->OnCancel();
	this->OnDestroy();
	this->PostNcDestroy();
}


BOOL member_registered::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	TCHAR ch = '*';
	((CEdit *)GetDlgItem(IDC_EDIT_registered_pwd))->SetPasswordChar(ch);


	ok = 0;

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

member member_registered::get_the_new_member()
{
	member to_return;
	//请求数据库，找到ID最大的那个
	_ConnectionPtr m_pConnection;
	_CommandPtr m_pCommand;
	_RecordsetPtr m_pRecordset;
	CString stSql;
	HRESULT hr = m_pConnection.CreateInstance("ADODB.Connection");
	if (SUCCEEDED(hr))
	{
		CString strConnection("Driver={sql server};server=127.0.0.1;database=MSCSDB;uid=sa;pwd=123456;");
		m_pConnection->Open((LPCTSTR)strConnection, "", "", adModeUnknown);
		m_pRecordset.CreateInstance("ADODB.Recordset");

		stSql.Format(_T("select * from member where id>=ALL (select id from member)"));
		m_pRecordset->Open((LPCTSTR)stSql, m_pConnection.GetInterfacePtr(), adOpenStatic, adLockOptimistic, adCmdText);
		_variant_t TheValue;
		to_return.if_login = 1;
		to_return.member_id = m_pRecordset->GetCollect("id");
		to_return.consumption = m_pRecordset->GetCollect("consumption");
		to_return.integral = m_pRecordset->GetCollect("integral");
		m_pRecordset->Close();
		m_pConnection->Close();
		m_pRecordset = NULL;
	}


	return to_return;
}


void member_registered::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	CString m_Password;
	GetDlgItem(IDC_EDIT_registered_pwd)->GetWindowText(m_Password);
	if (m_Password == "")
		m_Password = _T("请输入密码！");
	AfxMessageBox(m_Password);
}
