// Update_salesman.cpp: 实现文件
//

#include "pch.h"
#include "MFCApplication1.h"
#include "Update_salesman.h"
#include "afxdialogex.h"
#include "new_salesman.h"
#include "update_sal.h"

// Update_salesman 对话框

IMPLEMENT_DYNAMIC(Update_salesman, CDialogEx)

Update_salesman::Update_salesman(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_update_salesman, pParent)
{

}

Update_salesman::~Update_salesman()
{
}

void Update_salesman::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
}


BEGIN_MESSAGE_MAP(Update_salesman, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_add, &Update_salesman::OnBnClickedButtonadd)
	ON_BN_CLICKED(IDC_BUTTON_del, &Update_salesman::OnBnClickedButtondel)
	ON_BN_CLICKED(IDC_BUTTON_update, &Update_salesman::OnBnClickedButtonupdate)
END_MESSAGE_MAP()


// Update_salesman 消息处理程序


BOOL Update_salesman::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_CHECKBOXES);
	m_list.InsertColumn(0, _T("售货员ID"), 0, 130);
	m_list.InsertColumn(1, _T("售货员姓名"), 0, 130);
	m_list.InsertColumn(2, _T("售货员密码"), 0, 130);
	set_list();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void Update_salesman::set_list()
{
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

		stSql.Format(_T("select * from salesman"));
		m_pRecordset->Open((LPCTSTR)stSql, m_pConnection.GetInterfacePtr(), adOpenStatic, adLockOptimistic, adCmdText);

		CString strColumn[3];
		int iRowIndex = 0;

		_variant_t TheValue;
		while (!m_pRecordset->adoEOF)
		{
			TheValue = m_pRecordset->GetCollect("id").GetVARIANT();
			if (TheValue.vt != VT_NULL)
				strColumn[0] = TheValue;
			else
				strColumn[0] = "";
			m_list.InsertItem(iRowIndex, strColumn[0]);
			TheValue = m_pRecordset->GetCollect("name").GetVARIANT();
			if (TheValue.vt != VT_NULL)
				strColumn[1] = TheValue;
			else
				strColumn[1] = "";
			m_list.SetItemText(iRowIndex, 1, (_bstr_t)strColumn[1]);
			TheValue = m_pRecordset->GetCollect("pwd").GetVARIANT();
			if (TheValue.vt != VT_NULL)
				strColumn[2] = TheValue;
			else
				strColumn[2] = "";
			m_list.SetItemText(iRowIndex, 2, (_bstr_t)strColumn[2]);
			iRowIndex++;
			m_pRecordset->MoveNext();
		}
		m_pRecordset->Close();
		m_pConnection->Close();
		m_pRecordset = NULL;
	}
}

void Update_salesman::OnBnClickedButtonadd()
{
	// TODO: 在此添加控件通知处理程序代码
	new_salesman dlg;
	dlg.DoModal();
	m_list.DeleteAllItems();
	set_list();
}


void Update_salesman::OnBnClickedButtondel()
{
	// TODO: 在此添加控件通知处理程序代码
	for (int i = 0; i < m_list.GetItemCount(); i++)
		if (m_list.GetCheck(i))
			del_salesman(m_list.GetItemText(i, 0));
	m_list.DeleteAllItems();
	set_list();
}


void Update_salesman::del_salesman(CString id)
{
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
		strSql.Format(_T("delete from salesman where id =")+id);
		m_pCommand->ActiveConnection = m_pConnection;
		m_pCommand->CommandText = (LPCTSTR)strSql;
		m_pCommand->Execute(NULL, NULL, adCmdUnknown);
		m_pCommand = NULL;
		m_pConnection->Close();
		m_pConnection = NULL;
	}
}

void Update_salesman::OnBnClickedButtonupdate()
{
	// TODO: 在此添加控件通知处理程序代码
	int count = 0;
	int j = 0;
	for (int i = 0; i < m_list.GetItemCount(); i++)
		if (m_list.GetCheck(i))
		{
			count++;
			j = i;
		}
	if (count == 0)
	{
		AfxMessageBox(_T("请选择职员！"));
		return;
	}
	if (count > 1)
	{
		AfxMessageBox(_T("请勿选择多个职员！"));
		return;
	}
	update_sal dlg;
	dlg.NAME = m_list.GetItemText(j, 1);
	dlg.PWD = m_list.GetItemText(j, 2);
	dlg.ID = m_list.GetItemText(j, 0);
	dlg.DoModal();
	m_list.DeleteAllItems();
	set_list();
}