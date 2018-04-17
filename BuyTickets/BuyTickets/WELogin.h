#pragma once
#include "WininetHttp.h"

// CWELogin 对话框

class CWELogin : public CDialogEx
{
	DECLARE_DYNAMIC(CWELogin)

public:
	CWELogin(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CWELogin();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonLogin();


public:
	CString m_strName;
	CString m_strMima;
};
