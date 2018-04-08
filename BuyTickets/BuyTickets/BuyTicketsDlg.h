
// BuyTicketsDlg.h : 头文件
//

#pragma once
#include "WininetHttp.h"
#include "afxcmn.h"
#include "afxdtctl.h"
#include "afxwin.h"


// CBuyTicketsDlg 对话框
class CBuyTicketsDlg : public CDialogEx
{
// 构造
public:
	CBuyTicketsDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_BUYTICKETS_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
	CWininetHttp wininetHttp;

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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

	string strXingcheng;	//行程
	string strPerson;		//成人还是学生
	string strFromstation;	//起始站
	string strTostation;	//终点站
	string strFromdate;		//出发日期
	string strBackdate;		//返回日期
	afx_msg void OnBnClickedRadiodancheng();
	afx_msg void OnBnClickedRadiowangfan();
	afx_msg void OnBnClickedRadioputong();
	afx_msg void OnBnClickedRadioxuesheng();
	CDateTimeCtrl m_Fromdate;
	CDateTimeCtrl m_Backdate;
	afx_msg void OnClose();
	afx_msg void OnBnClickedButtontuozhanchaxun();
	CComboBox m_StrCombo_Train;
};
