// salesman.cpp: 实现文件
//

#include "pch.h"
#include "MFCApplication1.h"
#include "salesman.h"
#include "afxdialogex.h"
#include <string>


// salesman 对话框

IMPLEMENT_DYNAMIC(salesman, CDialogEx)

salesman::salesman(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_salesman, pParent)
{

}

salesman::~salesman()
{
}

void salesman::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_edit_mid);
	DDX_Control(pDX, IDC_EDIT2, m_edit_mter);
}


BEGIN_MESSAGE_MAP(salesman, CDialogEx)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON1, &salesman::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &salesman::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &salesman::OnBnClickedButton3)
END_MESSAGE_MAP()


// salesman 消息处理程序


void salesman::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialog* p = (CDialog*)AfxGetMainWnd();
	p->DestroyWindow();

	CDialogEx::OnClose();
}


BOOL salesman::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	m_edit_mid.SetWindowText(_T(""));

	TCHAR ch = '*';
	((CEdit *)GetDlgItem(IDC_EDIT_member_pwd))->SetPasswordChar(ch);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

//会员登录按钮
void salesman::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString member_id, member_pwd;
	GetDlgItemText(IDC_EDIT_member_id, member_id);
	GetDlgItemText(IDC_EDIT_member_pwd, member_pwd);

	//验证会员信息
	if (member_id == "" || member_pwd == "")
	{
		AfxMessageBox(_T("用户名密码不能为空！"));
		return;
	}
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


		stSql.Format(_T("SELECT * FROM member where ID = %s and pwd = '%s'"), member_id, member_pwd);


		m_pRecordset->Open((LPCTSTR)stSql, m_pConnection.GetInterfacePtr(), adOpenStatic, adLockOptimistic, adCmdText);

		if (!m_pRecordset->adoBOF)
		{
			//用户名密码正确，有数据，表示数据库里有该用户，说明该用户身份合法，允许继续使用
			AfxMessageBox(_T("登录成功！"));
			member_now.member_id = member_id;
			member_now.if_login = 1;
			//施工中
			member_now.integral = m_pRecordset->GetCollect("integral").GetVARIANT().date;
			member_now.consumption = m_pRecordset->GetCollect("consumption").GetVARIANT().date;
			m_edit_mid.SetWindowText(member_now.member_id);
			m_edit_mter.SetWindowText((CString)m_pRecordset->GetCollect("integral").GetVARIANT());
		}
		else
		{
			//身份不合法，请重新输入正确的用户名和密码
			::MessageBox(NULL, _T("用户名或密码不正确，请确认"), _T("登录信息有误"), MB_OK);
			return;
		}

	}

}



void salesman::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码

}


void salesman::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	CString m_Password;
	GetDlgItem(IDC_EDIT_member_pwd)->GetWindowText(m_Password);
	if (m_Password == "")
		m_Password = _T("请输入密码！");
	AfxMessageBox(m_Password);
}
