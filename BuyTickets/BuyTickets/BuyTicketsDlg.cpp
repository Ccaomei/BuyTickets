
// BuyTicketsDlg.cpp : ʵ���ļ�
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


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CBuyTicketsDlg �Ի���




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


// CBuyTicketsDlg ��Ϣ��������

BOOL CBuyTicketsDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵������ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ����Ӷ���ĳ�ʼ������

	//���ó�ʼ����ť״̬
	//GetDlgItem(IDC_RADIO_dancheng)->EnableWindow(TRUE);
	//GetDlgItem(IDC_RADIO_putong)->EnableWindow(TRUE);
	CButton* radio=(CButton*)GetDlgItem(IDC_RADIO_dancheng);
	radio->SetCheck(1);
	radio=(CButton*)GetDlgItem(IDC_RADIO_putong);
	radio->SetCheck(1);


	//�����б��ı�ͷ��Ϣ��ÿһ�еı�ʶ��
	CRect rect;
	m_ListTickets.GetClientRect(&rect); //��ȡ�б��ؼ���λ�úʹ�С
	m_ListTickets.SetExtendedStyle(m_ListTickets.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES);
	
	
	m_ListTickets.InsertColumn(0, _T("��ע"), LVCFMT_CENTER, rect.Width()/18, 0);
	m_ListTickets.InsertColumn(0, _T("����"), LVCFMT_CENTER, rect.Width()/18, 0);
	m_ListTickets.InsertColumn(0, _T("����"), LVCFMT_CENTER, rect.Width()/18, 0);
	m_ListTickets.InsertColumn(0, _T("Ӳ��"), LVCFMT_CENTER, rect.Width()/18, 0);
	m_ListTickets.InsertColumn(0, _T("����"), LVCFMT_CENTER, rect.Width()/18, 0);
	m_ListTickets.InsertColumn(0, _T("Ӳ��"), LVCFMT_CENTER, rect.Width()/18, 0);
	m_ListTickets.InsertColumn(0, _T("����"), LVCFMT_CENTER, rect.Width()/18, 0);
	m_ListTickets.InsertColumn(0, _T("����"), LVCFMT_CENTER, rect.Width()/18, 0);
	m_ListTickets.InsertColumn(0, _T("�߼�����"), LVCFMT_CENTER, rect.Width()/18, 0);
	m_ListTickets.InsertColumn(0, _T("������"), LVCFMT_CENTER, rect.Width()/18, 0);
	m_ListTickets.InsertColumn(0, _T("һ����"), LVCFMT_CENTER, rect.Width()/18, 0);
	m_ListTickets.InsertColumn(0, _T("������"), LVCFMT_CENTER, rect.Width()/18, 0);
	m_ListTickets.InsertColumn(0, _T("��ʱ"), LVCFMT_CENTER, rect.Width()/18, 0);
	m_ListTickets.InsertColumn(0, _T("����ʱ��"), LVCFMT_CENTER, rect.Width()/18, 0);
	m_ListTickets.InsertColumn(0, _T("����ʱ��"), LVCFMT_CENTER, rect.Width()/18, 0);
	m_ListTickets.InsertColumn(0, _T("����վ"), LVCFMT_CENTER, rect.Width()/18, 0);
	m_ListTickets.InsertColumn(0, _T("����վ"), LVCFMT_CENTER, rect.Width()/18, 0);
	m_ListTickets.InsertColumn(0, _T("����"), LVCFMT_CENTER, rect.Width()/18, 0);

	strPerson = "ADULT";

	//��ʼ����ʱ�򣬰�����վ�� �����������ص��ڴ���
	std::string retStrStation = wininetHttp.RequestJsonInfo("https://kyfw.12306.cn/otn/resources/js/framework/station_name.js", WE_Get, "", "");
	std::string strRetStrStation = wininetHttp.UtfToGbk(retStrStation.c_str());
	wininetHttp.ParseStationJsonInfo(strRetStrStation);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի���������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CBuyTicketsDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CBuyTicketsDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//ƥ��ini�ļ��ļ�ֵ��
string KeyValue(string key)
{
	TCHAR strModule[256];
	GetModuleFileName(NULL, strModule, 256); //�õ���ǰģ��·��
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
	// TODO: �ڴ����ӿؼ�֪ͨ�����������

	//�ӿڷ�����
	//Э�飺https:
	//������kyfw.12306.cn/
	//�ӿڣ�otn/leftTicket/query?
	//���������
	//
	//leftTicketDTO.train_date��������
	//leftTicketDTO.from_station�����ؼ����д
	//leftTicketDTO.to_stationĿ�ĵؼ����д
	//purpose_codes�˿�����(�ɶ�&ѧ��)��ADULT�ǳ��ˣ�ѧ����0X00


	std::string strUrl;
	// �Ȱ�url����Ϣ��֯��
	//��ȡʱ��
	CTime m_date;  //�������Ժ���ֻ��ʱ�����Ϣ,ʵ����������ͬʱ�������ں�ʱ����Ϣ
	m_Fromdate.GetTime(m_date); //�ѿؼ����ʱ����ϢŪ�����˰�.���������žͷ�����
	int year = m_date.GetYear();
	int month = m_date.GetMonth();
	int day = m_date.GetDay();
	//string strFromdate;		����ʱ��
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
	//string strFromdate;		����ʱ��
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

	//��ȡ��վ������Ӧ����
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



	//���url
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
	// TODO: �ڴ����ӿؼ�֪ͨ�����������
	strXingcheng = "";	//����
}


void CBuyTicketsDlg::OnBnClickedRadiowangfan()
{
	// TODO: �ڴ����ӿؼ�֪ͨ�����������
	strXingcheng = "";	//����
}


void CBuyTicketsDlg::OnBnClickedRadioputong()
{
	// TODO: �ڴ����ӿؼ�֪ͨ�����������
	strPerson = "ADULT";		//����
}


void CBuyTicketsDlg::OnBnClickedRadioxuesheng()
{
	// TODO: �ڴ����ӿؼ�֪ͨ�����������
	strPerson = "0X00";		//ѧ��
}


void CBuyTicketsDlg::OnClose()
{
	// TODO: �ڴ�������Ϣ������������/�����Ĭ��ֵ
	if(ticketInfo != NULL)
	{
		delete []ticketInfo;
		ticketInfo = NULL;
	}
	CDialogEx::OnClose();
}