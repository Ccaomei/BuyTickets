
// BuyTicketsDlg.h : ͷ�ļ�
//

#pragma once
#include "WininetHttp.h"
#include "afxcmn.h"
#include "afxdtctl.h"


// CBuyTicketsDlg �Ի���
class CBuyTicketsDlg : public CDialogEx
{
// ����
public:
	CBuyTicketsDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_BUYTICKETS_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
	CWininetHttp wininetHttp;

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonBeginconn();
	CListCtrl m_ListTickets;
	bool m_Raido_dancheng;
	bool m_Radio_wangfan;
	bool m_Radio_putong;
	bool m_Radio_xuesheng;

	string strXingcheng;	//�г�
	string strPerson;		//���˻���ѧ��
	string strFromstation;	//��ʼվ
	string strTostation;	//�յ�վ
	string strFromdate;		//��������
	string strBackdate;		//��������
	afx_msg void OnBnClickedRadiodancheng();
	afx_msg void OnBnClickedRadiowangfan();
	afx_msg void OnBnClickedRadioputong();
	afx_msg void OnBnClickedRadioxuesheng();
	CDateTimeCtrl m_Fromdate;
	CDateTimeCtrl m_Backdate;
	afx_msg void OnClose();
};