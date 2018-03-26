
// BuyTicketsDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "BuyTickets.h"
#include "BuyTicketsDlg.h"
#include "afxdialogex.h"
#include "ini.h"
#include <map>
//#include "WininetHttp.h"
#include <atlconv.h>
#include<iostream>
using namespace std;

extern TicketInfo *ticketInfo;
extern int AllTrainNum;

extern map<string, string>jianxie1_map;
extern map<string, string>hanzi_map;
extern map<string, string>pingyin_map;
extern map<string, string>jianxie2_map;
extern map<string, string>xuhao_map;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CBuyTicketsDlg 对话框




CBuyTicketsDlg::CBuyTicketsDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CBuyTicketsDlg::IDD, pParent)
	, m_Raido_dancheng(false)
	, m_Radio_wangfan(false)
	, m_Radio_putong(false)
	, m_Radio_xuesheng(false)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBuyTicketsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_Tickets, m_ListTickets);
	DDX_Control(pDX, IDC_DATETIMEPICKER_chufa, m_Fromdate);
	DDX_Control(pDX, IDC_DATETIMEPICKER_fancheng, m_Backdate);
}

BEGIN_MESSAGE_MAP(CBuyTicketsDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_BeginConn, &CBuyTicketsDlg::OnBnClickedButtonBeginconn)
	ON_BN_CLICKED(IDC_RADIO_dancheng, &CBuyTicketsDlg::OnBnClickedRadiodancheng)
	ON_BN_CLICKED(IDC_RADIO_wangfan, &CBuyTicketsDlg::OnBnClickedRadiowangfan)
	ON_BN_CLICKED(IDC_RADIO_putong, &CBuyTicketsDlg::OnBnClickedRadioputong)
	ON_BN_CLICKED(IDC_RADIO_xuesheng, &CBuyTicketsDlg::OnBnClickedRadioxuesheng)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CBuyTicketsDlg 消息处理程序

BOOL CBuyTicketsDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	//设置初始化按钮状态
	//GetDlgItem(IDC_RADIO_dancheng)->EnableWindow(TRUE);
	//GetDlgItem(IDC_RADIO_putong)->EnableWindow(TRUE);
	CButton* radio=(CButton*)GetDlgItem(IDC_RADIO_dancheng);
	radio->SetCheck(1);
	radio=(CButton*)GetDlgItem(IDC_RADIO_putong);
	radio->SetCheck(1);


	//加载列表的表头信息（每一列的标识）
	CRect rect;
	m_ListTickets.GetClientRect(&rect); //获取列表控件的位置和大小
	m_ListTickets.SetExtendedStyle(m_ListTickets.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES);
	
	
	m_ListTickets.InsertColumn(0, _T("备注"), LVCFMT_CENTER, rect.Width()/18, 0);
	m_ListTickets.InsertColumn(0, _T("其他"), LVCFMT_CENTER, rect.Width()/18, 0);
	m_ListTickets.InsertColumn(0, _T("无座"), LVCFMT_CENTER, rect.Width()/18, 0);
	m_ListTickets.InsertColumn(0, _T("硬座"), LVCFMT_CENTER, rect.Width()/18, 0);
	m_ListTickets.InsertColumn(0, _T("软座"), LVCFMT_CENTER, rect.Width()/18, 0);
	m_ListTickets.InsertColumn(0, _T("硬卧"), LVCFMT_CENTER, rect.Width()/18, 0);
	m_ListTickets.InsertColumn(0, _T("动卧"), LVCFMT_CENTER, rect.Width()/18, 0);
	m_ListTickets.InsertColumn(0, _T("软卧"), LVCFMT_CENTER, rect.Width()/18, 0);
	m_ListTickets.InsertColumn(0, _T("高级软卧"), LVCFMT_CENTER, rect.Width()/18, 0);
	m_ListTickets.InsertColumn(0, _T("二等座"), LVCFMT_CENTER, rect.Width()/18, 0);
	m_ListTickets.InsertColumn(0, _T("一等座"), LVCFMT_CENTER, rect.Width()/18, 0);
	m_ListTickets.InsertColumn(0, _T("商务座"), LVCFMT_CENTER, rect.Width()/18, 0);
	m_ListTickets.InsertColumn(0, _T("历时"), LVCFMT_CENTER, rect.Width()/18, 0);
	m_ListTickets.InsertColumn(0, _T("到达时间"), LVCFMT_CENTER, rect.Width()/18, 0);
	m_ListTickets.InsertColumn(0, _T("出发时间"), LVCFMT_CENTER, rect.Width()/18, 0);
	m_ListTickets.InsertColumn(0, _T("到达站"), LVCFMT_CENTER, rect.Width()/18, 0);
	m_ListTickets.InsertColumn(0, _T("出发站"), LVCFMT_CENTER, rect.Width()/18, 0);
	m_ListTickets.InsertColumn(0, _T("车次"), LVCFMT_CENTER, rect.Width()/18, 0);

	strPerson = "ADULT";

	//初始化的时候，把所有站点 都解析，加载到内存中
	std::string retStrStation = wininetHttp.RequestJsonInfo("https://kyfw.12306.cn/otn/resources/js/framework/station_name.js", WE_Get, "", "");
	std::string strRetStrStation = wininetHttp.UtfToGbk(retStrStation.c_str());
	wininetHttp.ParseStationJsonInfo(strRetStrStation);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CBuyTicketsDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CBuyTicketsDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CBuyTicketsDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//匹配ini文件的键值对
string KeyValue(string key)
{
	TCHAR strModule[256];
	GetModuleFileName(NULL, strModule, 256); //得到当前模块路径
	CString strDirPath( strModule );
	strDirPath = strDirPath.Left( strDirPath.ReverseFind('\\'));

	CString strIniPath;
	strIniPath.Format( _T("%s%s"), strDirPath, _T("\\RailwayStation.ini"));

	CIni _ini(strIniPath);
	CString strTemp(key.c_str());
	//strTemp.Format(_T("%s"), key.c_str());
	CString strState = _ini.GetValue(_T("STATION"), strTemp);

	string strUrl;
	CStringA strA;
	strA = strState;
	strUrl = strA;
	return strUrl;
}


void CBuyTicketsDlg::OnBnClickedButtonBeginconn()
{
	// TODO: 在此添加控件通知处理程序代码

	//接口分析：
	//协议：https:
	//域名：kyfw.12306.cn/
	//接口：otn/leftTicket/query?
	//请求参数：
	//
	//leftTicketDTO.train_date出发日期
	//leftTicketDTO.from_station出发地简称缩写
	//leftTicketDTO.to_station目的地简称缩写
	//purpose_codes乘客类型(成儿&学生)，ADULT是成人，学生是0X00


	std::string strUrl;
	// 先把url的信息组织好
	//获取时间
	CTime m_date;  //别看名字以后它只有时间的信息,实际上它可以同时保存日期和时间信息
	m_Fromdate.GetTime(m_date); //把控件里的时间信息弄过来了啊.接下来用着就方便了
	int year = m_date.GetYear();
	int month = m_date.GetMonth();
	int day = m_date.GetDay();
	//string strFromdate;		出发时间
	if((month > 0 && month < 10) && (day > 0 && day < 10))
	{
		sprintf((char*)strFromdate.c_str(), "%d-0%d-0%d", year, month, day);
	}
	else if(month > 0 && month < 10)
	{
		sprintf((char*)strFromdate.c_str(), "%d-0%d-%d", year, month, day);
	}
	else if(day > 0 && day < 10)
	{
		sprintf((char*)strFromdate.c_str(), "%d-%d-0%d", year, month, day);
	}
	else
	{
		sprintf((char*)strFromdate.c_str(), "%d-%d-%d", year, month, day);
	}

	m_Backdate.GetTime(m_date);
	year = m_date.GetYear();
	month = m_date.GetMonth();
	day = m_date.GetDay();
	//string strFromdate;		返回时间
	if((month > 0 && month < 10) && (day > 0 && day < 10))
	{
		sprintf((char*)strBackdate.c_str(), "%d-0%d-0%d", year, month, day);
	}
	else if(month > 0 && month < 10)
	{
		sprintf((char*)strBackdate.c_str(), "%d-0%d-%d", year, month, day);
	}
	else if(day > 0 && day < 10)
	{
		sprintf((char*)strBackdate.c_str(), "%d-%d-0%d", year, month, day);
	}
	else
	{
		sprintf((char*)strBackdate.c_str(), "%d-%d-%d", year, month, day);
	}

	//获取车站名及对应编码
	string strstation1;
	CString strFsta1;
	GetDlgItem(IDC_EDIT_fromstation)->GetWindowTextW(strFsta1);
	CStringA strA1;
	strA1 = strFsta1;
	strstation1 = strA1;
	bool isFondStr = false;
	map<string, string>::iterator map_it;
	for(map_it = jianxie1_map.begin(); map_it != jianxie1_map.end(); map_it++)
	{
		if(strcmp((*map_it).first.c_str(), strstation1.c_str()) == 0)
		{
			strFromstation = (*map_it).second;
			isFondStr = true;
			break;
		}
	}
	if(!isFondStr)
	{
		for(map_it = hanzi_map.begin(); map_it != hanzi_map.end(); map_it++)
		{
			if(strcmp((*map_it).first.c_str(), strstation1.c_str()) == 0)
			{
				strFromstation = (*map_it).second;
				isFondStr = true;
				break;
			}
		}
	}
	if(!isFondStr)
	{
		for(map_it = pingyin_map.begin(); map_it != pingyin_map.end(); map_it++)
		{
			if(strcmp((*map_it).first.c_str(), strstation1.c_str()) == 0)
			{
				strFromstation = (*map_it).second;
				isFondStr = true;
				break;
			}
		}
	}
	if(!isFondStr)
	{
		for(map_it = jianxie2_map.begin(); map_it != jianxie2_map.end(); map_it++)
		{
			if(strcmp((*map_it).first.c_str(), strstation1.c_str()) == 0)
			{
				strFromstation = (*map_it).second;
				isFondStr = true;
				break;
			}
		}
	}
	if(!isFondStr)
	{
		for(map_it = xuhao_map.begin(); map_it != xuhao_map.end(); map_it++)
		{
			if(strcmp((*map_it).first.c_str(), strstation1.c_str()) == 0)
			{
				strFromstation = (*map_it).second;
				isFondStr = true;
				break;
			}
		}
	}
	//strFromstation = KeyValue(strstation1);
	isFondStr = false;

	string strstation2;
	CString strFsta2;
	GetDlgItem(IDC_EDIT_deststation)->GetWindowTextW(strFsta2);
	CStringA strA2;
	strA2 = strFsta2;
	strstation2 = strA2;
	for(map_it = jianxie1_map.begin(); map_it != jianxie1_map.end(); map_it++)
	{
		if(strcmp((*map_it).first.c_str(), strstation2.c_str()) == 0)
		{
			strTostation = (*map_it).second;
			isFondStr = true;
			break;
		}
	}
	if(!isFondStr)
	{
		for(map_it = hanzi_map.begin(); map_it != hanzi_map.end(); map_it++)
		{
			if(strcmp((*map_it).first.c_str(), strstation2.c_str()) == 0)
			{
				strTostation = (*map_it).second;
				isFondStr = true;
				break;
			}
		}
	}
	if(!isFondStr)
	{
		for(map_it = pingyin_map.begin(); map_it != pingyin_map.end(); map_it++)
		{
			if(strcmp((*map_it).first.c_str(), strstation2.c_str()) == 0)
			{
				strTostation = (*map_it).second;
				isFondStr = true;
				break;
			}
		}
	}
	if(!isFondStr)
	{
		for(map_it = jianxie2_map.begin(); map_it != jianxie2_map.end(); map_it++)
		{
			if(strcmp((*map_it).first.c_str(), strstation2.c_str()) == 0)
			{
				strTostation = (*map_it).second;
				isFondStr = true;
				break;
			}
		}
	}
	if(!isFondStr)
	{
		for(map_it = xuhao_map.begin(); map_it != xuhao_map.end(); map_it++)
		{
			if(strcmp((*map_it).first.c_str(), strstation2.c_str()) == 0)
			{
				strTostation = (*map_it).second;
				isFondStr = true;
				break;
			}
		}
	}
	//strTostation = KeyValue(strstation2);



	//组合url
	strUrl = "https://kyfw.12306.cn/otn/leftTicket/queryO?leftTicketDTO.train_date=";
	strUrl += strFromdate.c_str();
	strUrl += "&leftTicketDTO.from_station=";
	strUrl += strFromstation;
	strUrl += "&leftTicketDTO.to_station=";
	strUrl += strTostation;
	strUrl += "&purpose_codes=";
	strUrl += strPerson;
	/*char buf[1024] = {0};
	CString str;
	GetDlgItem(IDC_EDIT_InputUrl)->GetWindowText(str); 
	string strUrl;
	CStringA strA;
	strA = str;
	strUrl = strA;*/
	//::GetDlgItemText(pWnd, IDC_EDIT_InputUrl, buf, 1024);
	//std::string strUrl = "https://kyfw.12306.cn/otn/leftTicket/queryO?leftTicketDTO.train_date=2018-03-23&leftTicketDTO.from_station=BJP&leftTicketDTO.to_station=ZZF&purpose_codes=ADULT";
	std::string strHostName;
	std::string strPageName;
	WORD sPort;
	//wininetHttp.ParseURLWeb(strUrl, strHostName, strPageName,sPort);
	std::string strHeader = "";
	std::string strPostData = "";
	std::string retStr = wininetHttp.RequestJsonInfo(strUrl, WE_Get, strHeader, strPostData);
	std::string strEnd = wininetHttp.UtfToGbk(retStr.c_str());

	USES_CONVERSION;
	
	std::string strJsonInfo = strEnd;
	wininetHttp.ParseJsonInfo(strJsonInfo);
	m_ListTickets.DeleteAllItems();
	for(int i = AllTrainNum -1 ; i >= 0; i--)
	{
		m_ListTickets.InsertItem(0, A2W(ticketInfo[i].station_train_code.c_str()));   
		m_ListTickets.SetItemText(0, 1, A2W(ticketInfo[i].from_station_name.c_str()));   
		m_ListTickets.SetItemText(0, 2, A2W(ticketInfo[i].to_station_name.c_str()));
		m_ListTickets.SetItemText(0, 3, A2W(ticketInfo[i].start_time.c_str()));
		m_ListTickets.SetItemText(0, 4, A2W(ticketInfo[i].arrive_time.c_str()));
		m_ListTickets.SetItemText(0, 5, A2W(ticketInfo[i].lishi.c_str()));
		m_ListTickets.SetItemText(0, 6, A2W(ticketInfo[i].swz_num.c_str()));
		m_ListTickets.SetItemText(0, 7, A2W(ticketInfo[i].zy_num.c_str()));
		m_ListTickets.SetItemText(0, 8, A2W(ticketInfo[i].ze_num.c_str()));
		m_ListTickets.SetItemText(0, 9, A2W(ticketInfo[i].gr_num.c_str()));
		m_ListTickets.SetItemText(0, 10, A2W(ticketInfo[i].rw_num.c_str()));
		m_ListTickets.SetItemText(0, 11, A2W(ticketInfo[i].dw_num.c_str()));
		m_ListTickets.SetItemText(0, 12, A2W(ticketInfo[i].yw_num.c_str()));
		m_ListTickets.SetItemText(0, 13, A2W(ticketInfo[i].rz_num.c_str()));
		m_ListTickets.SetItemText(0, 14, A2W(ticketInfo[i].yz_num.c_str()));
		m_ListTickets.SetItemText(0, 15, A2W(ticketInfo[i].wz_num.c_str()));
		m_ListTickets.SetItemText(0, 16, A2W(ticketInfo[i].qt_num.c_str()));
	}
	UpdateWindow();
}


void CBuyTicketsDlg::OnBnClickedRadiodancheng()
{
	// TODO: 在此添加控件通知处理程序代码
	strXingcheng = "";	//单程
}


void CBuyTicketsDlg::OnBnClickedRadiowangfan()
{
	// TODO: 在此添加控件通知处理程序代码
	strXingcheng = "";	//往返
}


void CBuyTicketsDlg::OnBnClickedRadioputong()
{
	// TODO: 在此添加控件通知处理程序代码
	strPerson = "ADULT";		//成人
}


void CBuyTicketsDlg::OnBnClickedRadioxuesheng()
{
	// TODO: 在此添加控件通知处理程序代码
	strPerson = "0X00";		//学生
}


void CBuyTicketsDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(ticketInfo != NULL)
	{
		delete []ticketInfo;
		ticketInfo = NULL;
	}
	CDialogEx::OnClose();
}
