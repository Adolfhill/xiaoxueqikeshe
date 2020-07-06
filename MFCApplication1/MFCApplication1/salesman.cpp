// salesman.cpp: 实现文件
//

#include "pch.h"
#include "MFCApplication1.h"
#include "salesman.h"
#include "afxdialogex.h"
#include "member_registered.h"
#include "pay.h"

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
	DDX_Control(pDX, IDC_EDIT_member_id, m_edit_mid_input);
	DDX_Control(pDX, IDC_EDIT_member_pwd, m_edit_mpwd_input);
	DDX_Control(pDX, IDC_LIST3, m_list);
	DDX_Control(pDX, IDC_EDIT3, m_edit_commodity_id);
	DDX_Control(pDX, IDC_EDIT4, m_edit_commodity_count);
}


BEGIN_MESSAGE_MAP(salesman, CDialogEx)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON1, &salesman::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &salesman::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &salesman::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON_member_signout, &salesman::OnBnClickedButtonmembersignout)
	ON_BN_CLICKED(IDC_BUTTON_add_to_list, &salesman::OnBnClickedButtonaddtolist)
	ON_BN_CLICKED(IDC_BUTTON4, &salesman::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON_select_all, &salesman::OnBnClickedButtonselectall)
	ON_BN_CLICKED(IDC_BUTTON_rev, &salesman::OnBnClickedButtonrev)
	ON_BN_CLICKED(IDC_BUTTON_del, &salesman::OnBnClickedButtondel)
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
	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_CHECKBOXES);
	m_edit_mid.SetWindowText(_T(""));

	TCHAR ch = '*';
	((CEdit *)GetDlgItem(IDC_EDIT_member_pwd))->SetPasswordChar(ch);

	//list初始化
	m_list.InsertColumn(0, _T("商品id"), 0, 100);
	m_list.InsertColumn(1, _T("商品价格"), 0, 100);
	m_list.InsertColumn(2, _T("购买数量"), 0, 100);
	//构建commodity_map
	commodity_map = get_the_map();

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
			//下面这两种方法都可以把CString转成float，但是都不能解决float的精度问题，不过或许这不重要？
			member_now.integral = _ttof((CString)m_pRecordset->GetCollect("integral").GetVARIANT());
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
	//退出会员登录
	OnBnClickedButtonmembersignout();
	//注册界面
	member_registered dlg;
	dlg.DoModal();
	if (!dlg.ok)
	{
		AfxMessageBox(_T("注册失败！"));
		return;
	}
	//注册成功
	member_now = dlg.member_now;
	AfxMessageBox(_T("注册成功！\n 您的ID为")+member_now.member_id);
	return;
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


void salesman::OnBnClickedButtonmembersignout()
{
	// TODO: 在此添加控件通知处理程序代码
	member_now.if_login = 0;
	member_now.member_id = "0";
	m_edit_mid.SetWindowText(_T(""));
	m_edit_mter.SetWindowText(_T(""));
	m_edit_mid_input.SetWindowText(_T(""));
	m_edit_mpwd_input.SetWindowText(_T(""));
}


void salesman::OnBnClickedButtonaddtolist()
{
	// TODO: 在此添加控件通知处理程序代码
	CString commodity_id, commodity_count, commodity_prise;
	int list_row = m_list.GetItemCount();
	GetDlgItemText(IDC_EDIT3, commodity_id);
	GetDlgItemText(IDC_EDIT4, commodity_count);
	//检查是否输入了正确的id
	if (!commodity_map.count(commodity_id))
	{
		AfxMessageBox(_T("ID错误！"));
		return;
	}
	float the_prise = commodity_map[commodity_id];
	//检查list中是否已有该ID,如果已有该ID,修改count即可
	int kkk;
	for (int i = 0; i < list_row; i++)
		if (commodity_id == m_list.GetItemText(i, 0))
		{
			kkk = _ttoi(m_list.GetItemText(i, 2));
			kkk += _ttoi(commodity_count);
			commodity_count.Format(_T("%d"), kkk);
			m_list.SetItemText(i, 2, commodity_count);
			return;
		}
	//如果没有该ID
	m_list.InsertItem(list_row, commodity_id);
	commodity_prise.Format(_T("%.2lf"), the_prise);
	m_list.SetItemText(list_row, 1, commodity_prise);
	m_list.SetItemText(list_row, 2, commodity_count);
	return;
}


std::map<CString, float> salesman::get_the_map()
{
	std::map<CString, float> to_return;
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

		stSql.Format(_T("select * from stock" ));
		m_pRecordset->Open((LPCTSTR)stSql, m_pConnection.GetInterfacePtr(), adOpenStatic, adLockOptimistic, adCmdText);
		_variant_t TheValue;
		while (!m_pRecordset->adoEOF)
		{
			to_return.insert(std::pair<CString, float>(m_pRecordset->GetCollect("id"), m_pRecordset->GetCollect("prise")));
			m_pRecordset->MoveNext();
		}
		m_pRecordset->Close();
		m_pConnection->Close();
		m_pRecordset = NULL;
	}
	return to_return;
}

void salesman::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	//计算价格
	float sum = 0;
	for (int i = 0; i < m_list.GetItemCount(); i++)
	{
		sum += _ttoi(m_list.GetItemText(i, 1))*_ttoi(m_list.GetItemText(i, 2));
	}
	if (member_now.consumption > 500)
	{
		AfxMessageBox(_T("总消费额达到500元 ，享受95折优惠"));
		sum *= 0.95;
	}
	pay dlg;
	dlg.sum = sum;
	if (member_now.if_login)
	{
		dlg.integral = member_now.integral;
	}
	else
	{
		dlg.integral = 0;
	}
	dlg.DoModal();
	if (!dlg.ok)
	{
		AfxMessageBox(_T("取消支付！"));
		return;
	}
	AfxMessageBox(_T("支付成功！"));
	member_now.integral += dlg.sum;
	member_now.integral -= float(dlg.use_integral);
	//现在使用的积分保存在dlg.use_integral中，接下来要做的就是修改下面两个表了
	//修改member表
	if(member_now.if_login)
		Update_member(dlg.sum);
	//修改stock表
	CString stock_id, stock_count;
	for (int i = 0; i < m_list.GetItemCount(); i++)
	{
		stock_id = m_list.GetItemText(i, 0);
		stock_count = m_list.GetItemText(i, 2);
		Update_stock(stock_id,stock_count);
	}
	//自动退出会员并清空list
	OnBnClickedButtonmembersignout();
	m_list.DeleteAllItems();
}

void salesman::Update_stock(CString stock_id, CString stock_count)
{
	_ConnectionPtr m_pConnection;//数据库连接对象
	_CommandPtr m_pCommand;//数据库命令对象
	HRESULT hresult = m_pConnection.CreateInstance("ADODB.Connection"); //创建Connection对象
	if (SUCCEEDED(hresult))
	{
		m_pCommand.CreateInstance("ADODB.Command");
		CString strConnection("Driver={sql server};server=127.0.0.1;database=MSCSDB;uid=sa;pwd=123456;");
		m_pConnection->Open((LPCTSTR)strConnection, "", "", adModeUnknown);
		CString strSql;
		strSql.Format(_T("update Stock set stock=stock-") + stock_count + _T(" where id=") + stock_id);
		m_pCommand->ActiveConnection = m_pConnection;
		m_pCommand->CommandText = (LPCTSTR)strSql;
		m_pCommand->Execute(NULL, NULL, adCmdUnknown);
		m_pCommand = NULL;
		m_pConnection->Close();
		m_pConnection = NULL;

	}
}


void salesman::Update_member(float sum)
{
	float new_co = member_now.consumption + sum;
	CString strco;
	strco.Format(_T("%.2f"), new_co);
	float new_int = member_now.integral;
	CString strin;
	strin.Format(_T("%.2f"), new_int);

	_ConnectionPtr m_pConnection;//数据库连接对象
	_CommandPtr m_pCommand;//数据库命令对象
	HRESULT hresult = m_pConnection.CreateInstance("ADODB.Connection"); //创建Connection对象
	if (SUCCEEDED(hresult))
	{
		m_pCommand.CreateInstance("ADODB.Command");
		CString strConnection("Driver={sql server};server=127.0.0.1;database=MSCSDB;uid=sa;pwd=123456;");
		m_pConnection->Open((LPCTSTR)strConnection, "", "", adModeUnknown);
		CString strSql;
		strSql.Format(_T("update member set consumption=" + strco + ",integral=" + strin + " where id=" + member_now.member_id));
		m_pCommand->ActiveConnection = m_pConnection;
		m_pCommand->CommandText = (LPCTSTR)strSql;
		m_pCommand->Execute(NULL, NULL, adCmdUnknown);
		m_pCommand = NULL;
		m_pConnection->Close();
		m_pConnection = NULL;

	}
}



void salesman::OnBnClickedButtonselectall()
{
	// TODO: 在此添加控件通知处理程序代码
	for (int i = 0; i < m_list.GetItemCount(); i++)
		m_list.SetCheck(i);
}


void salesman::OnBnClickedButtonrev()
{
	// TODO: 在此添加控件通知处理程序代码
	for (int i = 0; i < m_list.GetItemCount(); i++)
		m_list.SetCheck(i, !m_list.GetCheck(i));
}


void salesman::OnBnClickedButtondel()
{
	// TODO: 在此添加控件通知处理程序代码
	for (int i = 0; i < m_list.GetItemCount(); i++)
		if (m_list.GetCheck(i))
		{
			m_list.DeleteItem(i--);
		}
}
