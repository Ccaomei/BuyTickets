#pragma once
#include "WininetHttp.h"

// CWELogin �Ի���

class CWELogin : public CDialogEx
{
	DECLARE_DYNAMIC(CWELogin)

public:
	CWELogin(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CWELogin();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonLogin();


public:
	CString m_strName;
	CString m_strMima;
};