#pragma once

#include <iostream>
#include <Windows.h>
#include <WinInet.h>
#include <vector>
using namespace std;


#define  READ_BUFFER_SIZE 4096

enum HttpInterfaceError
{
	WE_Success			= 0,
	WE_InitErr			= 1,
	WE_ConnectErr		= 2,
	WE_SendErr			= 3,
	WE_QueryErr			= 4,
	WE_404				= 5,
	WE_IllegalUrl		= 6,
	WE_CreateFileErr	= 7,
	WE_DownloadErr		= 8,
	WE_QueryIPErr		= 9,
	WE_SocketErr		= 10,
	WE_UserCancel		= 11,
	WE_HeaderErr		= 12,
	WE_ParamErr			= 13,
	WE_UnknowErr		= 14,
};

enum HttpRequest
{
	WE_Get,
	WE_Post,
};


struct TicketInfo{
	string station_train_code;	//����		3��λ��
	string from_station_name;	//ʼ��վ    6��λ��
	string to_station_name;		//�յ�վ    7��λ��
	string start_time;			//����ʱ��  8��λ��
	string arrive_time;			//�ִ�ʱ��	9��λ��
	string lishi;				//����ʱ��  10��λ��
	string swz_num;				//������    32��25��λ��
	string zy_num;				//һ����	31��λ��
	string ze_num;				//������	30��λ��
	string gr_num;				//�߼�����	21��λ��
	string rw_num;				//����		23��λ��
	string dw_num;				//����		27��λ��
	string yw_num;				//Ӳ��		28��λ��
	string rz_num;				//����		24��λ��
	string yz_num;				//Ӳ��		29��λ��
	string wz_num;				//����		26��λ��
	string qt_num;				//������Ϣ	22��λ��
};





// CWininetHttp

class CWininetHttp : public CWnd
{
	DECLARE_DYNAMIC(CWininetHttp)

public:
	CWininetHttp();
	virtual ~CWininetHttp();

protected:
	DECLARE_MESSAGE_MAP()


public:
	//  ͨ��HTTP����Get��Post��ʽ��ȡJSON��Ϣ 
	const std::string RequestJsonInfo(const std::string &strUrl, HttpRequest type = WE_Get, std::string lpHeade = "", std::string lpPostData = "");

public:
	// ��������Json���� 
	void ParseJsonInfo(const std::string &strJsonInfo);

	//����վ���Json����
	void ParseStationJsonInfo(const std::string &strStationJsonInfo);

	// �رվ�� 
	void Release();

	// �ͷž�� 
	void ReleaseHandle(HINTERNET & hInternet);

	// ����URL��ַ 
	void ParseURLWeb(std::string strUrl, std::string &strHostName, std::string &strPageName, WORD &sPort);

	// UTF-8תΪGBK2312
	char* UtfToGbk(const char* utf8);



private:
	HINTERNET	m_hSession;
	HINTERNET	m_hConnect;
	HINTERNET	m_hRequest;
	HttpInterfaceError	m_error;
};

