// update_sal.cpp: 实现文件
//

#include "pch.h"
#include "MFCApplication1.h"
#include "update_sal.h"
#include "afxdialogex.h"


// update_sal 对话框

IMPLEMENT_DYNAMIC(update_sal, CDialogEx)

update_sal::update_sal(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

update_sal::~update_sal()
{
}

void update_sal::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_id, m_edit_id);
	DDX_Control(pDX, IDC_EDIT_pwd, m_edit_pwd);
	DDX_Control(pDX, IDC_EDIT_name, m_edit_name);
}


BEGIN_MESSAGE_MAP(update_sal, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &update_sal::OnBnClickedButton1)
END_MESSAGE_MAP()


// update_sal 消息处理程序


void update_sal::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString id, pwd, name;
	GetDlgItemText(IDC_EDIT_id, id);
	GetDlgItemText(IDC_EDIT_pwd, pwd);
	GetDlgItemText(IDC_EDIT_name, name);
	if (name == "")
		name = _T("NULL");
	else
		name = _T("'") + name + _T("'");
	//请求数据库
	_ConnectionPtr m_pConnection;//数据库连接对象
	_CommandPtr m_pCommand;//数据库命令对象
	HRESULT hresult = m_pConnection.CreateInstance("ADODB.Connection"); //创建Connection对象
	if (SUCCEEDED(hresult))
	{
		m_pCommand.CreateInstance("ADODB.Command");
		CString strConnection("Driver={sql server};server=127.0.0.1;database=MSCSDB;uid=sa;pwd=123456;");
		m_pConnection->Open((LPCTSTR)strConnection, "", "", adModeUnknown);
		CString strSql;
		strSql.Format(_T("update salesman set Pwd='%s', name="+name+" where id = '%s'"), pwd, id);
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


BOOL update_sal::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	m_edit_id.SetWindowText(ID);
	m_edit_pwd.SetWindowText(PWD);
	m_edit_name.SetWindowText(NAME);


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
