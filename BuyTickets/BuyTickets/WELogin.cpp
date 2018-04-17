// WELogin.cpp : 实现文件
//

#include "stdafx.h"
#include "BuyTickets.h"
#include "WELogin.h"
#include "afxdialogex.h"


// CWELogin 对话框

IMPLEMENT_DYNAMIC(CWELogin, CDialogEx)

CWELogin::CWELogin(CWnd* pParent /*=NULL*/)
	: CDialogEx(CWELogin::IDD, pParent)
{

}

CWELogin::~CWELogin()
{
}

void CWELogin::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CWELogin, CDialogEx)
	ON_BN_CLICKED(ID_Button_Login, &CWELogin::OnBnClickedButtonLogin)
END_MESSAGE_MAP()


// CWELogin 消息处理程序


void CWELogin::OnBnClickedButtonLogin()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItemText( IDC_EDIT_UserName, m_strName );
	GetDlgItemText( IDC_EDIT_Mima, m_strMima );
	CStringA strA1;
	strA1 = m_strName;
	string strUserName = strA1;
	CStringA strA2;
	strA2 = m_strMima;
	string strMima = strA2;



}
