// view_seven_days.cpp: 实现文件
//

#include "pch.h"
#include "MFCApplication1.h"
#include "view_seven_days.h"
#include "afxdialogex.h"


// view_seven_days 对话框

IMPLEMENT_DYNAMIC(view_seven_days, CDialogEx)

view_seven_days::view_seven_days(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_7days, pParent)
{

}

view_seven_days::~view_seven_days()
{
}

void view_seven_days::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
}


BEGIN_MESSAGE_MAP(view_seven_days, CDialogEx)
END_MESSAGE_MAP()


// view_seven_days 消息处理程序


BOOL view_seven_days::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	m_list.InsertColumn(0, _T("日期"), 0, 130);
	m_list.InsertColumn(1, _T("销量"), 0, 130);
	set_list();


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

void view_seven_days::set_list()
{
	_ConnectionPtr m_pConnection;
	_CommandPtr m_pCommand;
	_RecordsetPtr m_pRecordset;
	CString stSql;
	HRESULT hr = m_pConnection.CreateInstance("ADODB.Connection");
	if (SUCCEEDED(hr))
	{
		CString temp;
		CString strConnection("Driver={sql server};server=127.0.0.1;database=MSCSDB;uid=sa;pwd=123456;");
		m_pConnection->Open((LPCTSTR)strConnection, "", "", adModeUnknown);
		m_pRecordset.CreateInstance("ADODB.Recordset");

		stSql.Format(_T("select the_time,SUM(stock_count)'count' from (select convert(varchar(20),the_time,111)'the_time',stock_count from order_info,order_details where order_info.id=order_details.id and stock_id=%s) as kk group by the_time"), ID);
		m_pRecordset->Open((LPCTSTR)stSql, m_pConnection.GetInterfacePtr(), adOpenStatic, adLockOptimistic, adCmdText);
		int iRowIndex = 0;
		while (!m_pRecordset->adoEOF)
		{
			temp = m_pRecordset->GetCollect("the_time").GetVARIANT();
			m_list.InsertItem(iRowIndex,temp);
			temp = m_pRecordset->GetCollect("count").GetVARIANT();
			m_list.SetItemText(iRowIndex, 1, temp);
			iRowIndex++;
			m_pRecordset->MoveNext();
		}
		m_pRecordset->Close();
		m_pConnection->Close();
		m_pRecordset = NULL;
	}

}
