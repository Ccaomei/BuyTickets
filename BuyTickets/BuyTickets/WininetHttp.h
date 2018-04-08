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
	string train_code_xuhao;	//车次序号  2号位置
	string station_train_code;	//车次		3号位置
	string from_station_name;	//始发站    6号位置
	string to_station_name;		//终点站    7号位置
	string start_time;			//出发时间  8号位置
	string arrive_time;			//抵达时间	9号位置
	string lishi;				//经历时间  10号位置
	string swz_num;				//商务座    32或25号位置
	string zy_num;				//一等座	31号位置
	string ze_num;				//二等座	30号位置
	string gr_num;				//高级软卧	21号位置
	string rw_num;				//软卧		23号位置
	string dw_num;				//动卧		27号位置
	string yw_num;				//硬卧		28号位置
	string rz_num;				//软座		24号位置
	string yz_num;				//硬座		29号位置
	string wz_num;				//无座		26号位置
	string qt_num;				//其他信息	22号位置
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
	//  通过HTTP请求：Get或Post方式获取JSON信息 
	const std::string RequestJsonInfo(const std::string &strUrl, HttpRequest type = WE_Get, std::string lpHeade = "", std::string lpPostData = "");

public:
	// 解析卡口Json数据 
	void ParseJsonInfo(const std::string &strJsonInfo);

	//解析站点的Json数据
	void ParseStationJsonInfo(const std::string &strStationJsonInfo);

	// 关闭句柄 
	void Release();

	// 释放句柄 
	void ReleaseHandle(HINTERNET & hInternet);

	// 解析URL地址 
	void ParseURLWeb(std::string strUrl, std::string &strHostName, std::string &strPageName, WORD &sPort);

	// UTF-8转为GBK2312
	char* UtfToGbk(const char* utf8);

	//解析一辆车次的所有站点json数据
	void ParseTrainStationJsonInfo(const std::string &strTrainStationJsonInfo);



private:
	HINTERNET	m_hSession;
	HINTERNET	m_hConnect;
	HINTERNET	m_hRequest;
	HttpInterfaceError	m_error;
};


