// view_member.cpp: 实现文件
//

#include "pch.h"
#include "MFCApplication1.h"
#include "view_member.h"
#include "afxdialogex.h"
#include "view_member_details.h"


// view_member 对话框

IMPLEMENT_DYNAMIC(view_member, CDialogEx)

view_member::view_member(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_view_member, pParent)
{

}

view_member::~view_member()
{
}

void view_member::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
}


BEGIN_MESSAGE_MAP(view_member, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &view_member::OnBnClickedButton1)
END_MESSAGE_MAP()


// view_member 消息处理程序


BOOL view_member::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化


	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_CHECKBOXES);
	m_list.InsertColumn(0, _T("会员ID"), 0, 130);
	m_list.InsertColumn(1, _T("会员姓名"), 0, 130);
	m_list.InsertColumn(2, _T("会员总消费"), 0, 130);
	m_list.InsertColumn(3, _T("会员积分"), 0, 130);
	set_list();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void view_member::set_list()
{
	CString temp;
	float t;
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

		stSql.Format(_T("select * from member"));
		m_pRecordset->Open((LPCTSTR)stSql, m_pConnection.GetInterfacePtr(), adOpenStatic, adLockOptimistic, adCmdText);

		CString strColumn[4];
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
			TheValue = m_pRecordset->GetCollect("member_name").GetVARIANT();
			if (TheValue.vt != VT_NULL)
				strColumn[1] = TheValue;
			else
				strColumn[1] = "";
			m_list.SetItemText(iRowIndex, 1, (_bstr_t)strColumn[1]);
			t = m_pRecordset->GetCollect("consumption").GetVARIANT().date;
			temp.Format(_T("%.2f"), t);
			m_list.SetItemText(iRowIndex, 2, temp);
			t = m_pRecordset->GetCollect("integral").GetVARIANT().date;
			temp.Format(_T("%.2f"), t);
			m_list.SetItemText(iRowIndex, 3, temp);
			iRowIndex++;
			m_pRecordset->MoveNext();
		}
		m_pRecordset->Close();
		m_pConnection->Close();
		m_pRecordset = NULL;
	}
}

void view_member::OnBnClickedButton1()
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
		AfxMessageBox(_T("请选择要查看的会员！"));
		return;
	}
	if (count > 1)
	{
		AfxMessageBox(_T("请勿选择多个会员！"));
		return;
	}
	view_member_details dlg;
	dlg.ID = m_list.GetItemText(j, 0);
	dlg.DoModal();
}
