// stock.cpp: 实现文件
//

#include "pch.h"
#include "MFCApplication1.h"
#include "stock.h"
#include "afxdialogex.h"
#include "addstock.h"
#include "apd_the_stock.h"
#include "view_seven_days.h"


// stock 对话框

IMPLEMENT_DYNAMIC(stock, CDialogEx)

stock::stock(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_stock, pParent)
{

}

stock::~stock()
{
}

void stock::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
}


BEGIN_MESSAGE_MAP(stock, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_add, &stock::OnBnClickedButtonadd)
	ON_BN_CLICKED(IDC_BUTTON_del, &stock::OnBnClickedButtondel)
	ON_BN_CLICKED(IDC_BUTTON_apd_stock, &stock::OnBnClickedButtonapdstock)
	ON_BN_CLICKED(IDC_BUTTON1, &stock::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &stock::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &stock::OnBnClickedButton3)
END_MESSAGE_MAP()


// stock 消息处理程序


BOOL stock::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_CHECKBOXES);
	m_list.InsertColumn(0, _T("商品ID"), 0, 130);
	m_list.InsertColumn(1, _T("商品名称"), 0, 130);
	m_list.InsertColumn(2, _T("商品售价"), 0, 130);
	m_list.InsertColumn(3, _T("商品库存"), 0, 130);
	set_list();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void stock::set_list()
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

		stSql.Format(_T("select * from stock"));
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
			TheValue = m_pRecordset->GetCollect("name").GetVARIANT();
			if (TheValue.vt != VT_NULL)
				strColumn[1] = TheValue;
			else
				strColumn[1] = "";
			m_list.SetItemText(iRowIndex, 1, (_bstr_t)strColumn[1]);
			TheValue = m_pRecordset->GetCollect("prise").GetVARIANT();
			if (TheValue.vt != VT_NULL)
				strColumn[2] = TheValue;
			else
				strColumn[2] = "";
			m_list.SetItemText(iRowIndex, 2, (_bstr_t)strColumn[2]);
			TheValue = m_pRecordset->GetCollect("stock").GetVARIANT();
			if (TheValue.vt != VT_NULL)
				strColumn[3] = TheValue;
			else
				strColumn[3] = "";
			m_list.SetItemText(iRowIndex, 3, (_bstr_t)strColumn[3]);
			iRowIndex++;
			m_pRecordset->MoveNext();
		}
		m_pRecordset->Close();
		m_pConnection->Close();
		m_pRecordset = NULL;
	}
}

void stock::del_that(CString id)
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
		strSql.Format(_T("delete from stock where id=") + id);
		m_pCommand->ActiveConnection = m_pConnection;
		m_pCommand->CommandText = (LPCTSTR)strSql;
		m_pCommand->Execute(NULL, NULL, adCmdUnknown);
		m_pCommand = NULL;
		m_pConnection->Close();
		m_pConnection = NULL;
	}
}

void stock::OnBnClickedButtonadd()
{
	// TODO: 在此添加控件通知处理程序代码
	addstock dlg;
	dlg.DoModal();
	if (dlg.ok)
	{
		AfxMessageBox(_T("添加成功！"));
		m_list.DeleteAllItems();
		set_list();
	}
}


void stock::OnBnClickedButtondel()
{
	// TODO: 在此添加控件通知处理程序代码
	for (int i = 0; i < m_list.GetItemCount(); i++)
		if (m_list.GetCheck(i))
			del_that(m_list.GetItemText(i, 0));
	m_list.DeleteAllItems();
	set_list();
}


void stock::OnBnClickedButtonapdstock()
{
	// TODO: 在此添加控件通知处理程序代码
	for (int i = 0; i < m_list.GetItemCount(); i++)
		if (m_list.GetCheck(i))
		{
			apd_the_stock dlg;
			dlg.id = m_list.GetItemText(i, 0);
			dlg.name = m_list.GetItemText(i, 1);
			dlg.prise = m_list.GetItemText(i, 2);
			dlg.stock = m_list.GetItemText(i, 3);
			dlg.DoModal();
			if (dlg.end_upd)
				break;
			AfxMessageBox(_T("修改成功！"));
		}
	m_list.DeleteAllItems();
	set_list();
}

void stock::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	for (int i = 0; i < m_list.GetItemCount(); i++)
		m_list.SetCheck(i);
}


void stock::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	for (int i = 0; i < m_list.GetItemCount(); i++)
		m_list.SetCheck(i, !m_list.GetCheck(i));
}


void stock::OnBnClickedButton3()
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
		AfxMessageBox(_T("请选择要查看的商品！"));
		return;
	}
	if (count > 1)
	{
		AfxMessageBox(_T("请勿选择多个商品！"));
		return;
	}
	view_seven_days dlg;
	dlg.ID = m_list.GetItemText(j, 0);
	dlg.DoModal();
}
