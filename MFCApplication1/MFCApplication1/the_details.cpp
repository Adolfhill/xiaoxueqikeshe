// the_details.cpp: 实现文件
//

#include "pch.h"
#include "MFCApplication1.h"
#include "the_details.h"
#include "afxdialogex.h"


// the_details 对话框

IMPLEMENT_DYNAMIC(the_details, CDialogEx)

the_details::the_details(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_the_details, pParent)
{

}

the_details::~the_details()
{
}

void the_details::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
}

void the_details::set_list()
{
	CString temp;
	int t;
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

		stSql.Format(_T("select * from order_details where id=") + ID);
		m_pRecordset->Open((LPCTSTR)stSql, m_pConnection.GetInterfacePtr(), adOpenStatic, adLockOptimistic, adCmdText);

		int iRowIndex = 0;

		_variant_t TheValue;
		while (!m_pRecordset->adoEOF)
		{
			t = m_pRecordset->GetCollect("stock_id").GetVARIANT().intVal;
			temp.Format(_T("%d"), t);
			m_list.InsertItem(iRowIndex, temp);

			t = m_pRecordset->GetCollect("stock_count").GetVARIANT().intVal;
			temp.Format(_T("%d"), t);
			m_list.SetItemText(iRowIndex, 1, temp);

			iRowIndex++;
			m_pRecordset->MoveNext();
		}
		m_pRecordset->Close();
		m_pConnection->Close();
		m_pRecordset = NULL;
	}
}


BEGIN_MESSAGE_MAP(the_details, CDialogEx)
END_MESSAGE_MAP()


// the_details 消息处理程序


BOOL the_details::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_CHECKBOXES);
	m_list.InsertColumn(0, _T("商品ID"), 0, 130);
	m_list.InsertColumn(1, _T("数量"), 0, 130);
	set_list();


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
