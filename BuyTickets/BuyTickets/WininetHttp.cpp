// WininetHttp.cpp : 实现文件
//

#include "stdafx.h"
#include "BuyTickets.h"
#include "WininetHttp.h"
#include <fstream>
#include <cstring> 
#include <map>

#include "include/json/json.h"

#include <tchar.h>
#pragma comment(lib, "Wininet.lib")

using namespace Json;
// CWininetHttp

TicketInfo *ticketInfo = NULL;
int AllTrainNum = 0;

IMPLEMENT_DYNAMIC(CWininetHttp, CWnd)

CWininetHttp::CWininetHttp()
{

}

CWininetHttp::~CWininetHttp()
{
}


BEGIN_MESSAGE_MAP(CWininetHttp, CWnd)
END_MESSAGE_MAP()



// CWininetHttp 消息处理程序
const std::string CWininetHttp::RequestJsonInfo(const std::string &lpUrl, HttpRequest type /* = WE_Get */, std::string strHeader /* = "" */, std::string strPostData /* = "" */)
{
	std::string strRet = "";
	try
	{
		if(lpUrl.empty())
		{
			throw WE_ParamErr;
		}
		Release();

		m_hSession = InternetOpen(_T("Http-connect"), INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, NULL);
		if(m_hSession == NULL)
		{
			throw WE_InitErr;
		}

		INTERNET_PORT port = INTERNET_DEFAULT_HTTPS_PORT;
		std::string strHostName = "";	//"kyfw.12306.cn";
		std::string strPageName = "";	//"/otn/leftTicket/queryO?leftTicketDTO.train_date=2018-04-01&leftTicketDTO.from_station=BJP&leftTicketDTO.to_station=XUN&purpose_codes=ADULT";

		ParseURLWeb(lpUrl, strHostName, strPageName, port);

		//printf("lpUrl:%s,\nstrHostName:%s,\nstrPageName:%s,\nport:%d\n",lpUrl.c_str(),strHostName.c_str(),strPageName.c_str(),(int)port);

		m_hConnect = InternetConnectA(m_hSession, strHostName.c_str(), port, NULL, NULL, INTERNET_SERVICE_HTTP, NULL, NULL);
		if(m_hConnect == NULL)
		{
			int num = GetLastError();
			AfxMessageBox(_T("InternetConnectA"));
			throw WE_ConnectErr;
		}

		std::string strRequestType;
		if(type == WE_Get)
		{
			strRequestType = "GET";
		}
		else
		{
			strRequestType = "POST";
		}
		DWORD dwHttpOpenRequestFlags =  
			//flags common to open functions  
			INTERNET_FLAG_RELOAD |  
			//flags  
			//INTERNET_FLAG_ASYNC |  
			//additional cache flags  
			//INTERNET_FLAG_DONT_CACHE |  
			//additional flags  
			INTERNET_FLAG_SECURE |//启用ssl模式  
			INTERNET_FLAG_KEEP_CONNECTION |  
			INTERNET_FLAG_NO_AUTO_REDIRECT |  
			INTERNET_FLAG_READ_PREFETCH |  
			INTERNET_FLAG_NO_COOKIES |  
			INTERNET_FLAG_NO_AUTH |  
			INTERNET_FLAG_RESTRICTED_ZONE |  
			INTERNET_FLAG_CACHE_IF_NET_FAIL |  
			//ssl ignore flags  
			INTERNET_FLAG_IGNORE_REDIRECT_TO_HTTP |//忽略ssl模式下的https->http跳转  
			INTERNET_FLAG_IGNORE_CERT_CN_INVALID |//忽略ssl模式下的证书名称错误  
			//more cache flags  
			INTERNET_FLAG_NO_UI |  
			0;  
		//m_hRequest = HttpOpenRequestA(m_hConnect, strRequestType.c_str(), strPageName.c_str(), "HTTP/1.1", NULL, NULL, INTERNET_FLAG_RELOAD | INTERNET_FLAG_IGNORE_REDIRECT_TO_HTTP, NULL);
		m_hRequest = HttpOpenRequestA(m_hConnect, "GET", strPageName.c_str(), "HTTP_VERSION", NULL, NULL, dwHttpOpenRequestFlags, 0);
		if(m_hRequest == NULL)
		{
			throw WE_InitErr;
		}

		DWORD dwHeaderSize = (strHeader.empty()) ? 0 : strlen(strHeader.c_str());

		bool bRet = false;
		if(WE_Get == type)
		{
			bRet = HttpSendRequestA(m_hRequest, strHeader.c_str(), dwHeaderSize, NULL, 0);
		}
		else
		{
			DWORD dwSize = (strPostData.empty()) ? 0 : strlen(strPostData.c_str());
			bRet = HttpSendRequestA(m_hRequest, strHeader.c_str(), dwHeaderSize, (LPVOID)strPostData.c_str(), dwSize);
		}
		if(!bRet)
		{
			throw WE_SendErr;
		}

		char szBuffer[READ_BUFFER_SIZE + 1] = {0};
		DWORD dwReadSize = READ_BUFFER_SIZE;
		if(!HttpQueryInfoA(m_hRequest, HTTP_QUERY_RAW_HEADERS, szBuffer, &dwReadSize, NULL))//查询一个http请求的信息
		{
			throw WE_QueryErr;
		}
		if(NULL != strstr(szBuffer, "404"))
		{
			throw WE_404;
		}

		while(true)
		{
			bRet = InternetReadFile(m_hRequest, szBuffer, READ_BUFFER_SIZE, &dwReadSize);
			if(!bRet || (dwReadSize == 0))
			{
				break;
			}
			szBuffer[dwReadSize] = '\0';
			strRet.append(szBuffer);
		}
	}
	catch(HttpInterfaceError error)
	{
		m_error = error;
	}
	return std::move(strRet);
}
vector<string> EveryTicketVec;  
//打印容器vector    
void printVector(vector<string> vector1){  
	for(int i=0;i<int(vector1.size());i++){    
		cout<<vector1[i]<<endl;    
	}    
}  
//split函数  
vector<string> SPlit(string str,string separator)
{    
	vector<string> result;  
	result.clear();
	int cutAt;    
	while((cutAt = str.find_first_of(separator))!=str.npos)
	{    
		if(cutAt>0)
		{    
			result.push_back(str.substr(0,cutAt));  
		} 
		else if(cutAt == 0)
		{
			result.push_back("-");
		}
		str=str.substr(cutAt+1);    
	}    
	if(str.length()>0){    
		result.push_back(str);    
	}    
	return result;    
}  


// 解析Json数据
void CWininetHttp::ParseJsonInfo(const std::string &strJsonInfo)
{
	Json::Reader reader;		 //解析json用Json::Reader
	Json::Value value;			 //可以代表任意类型

	if(!reader.parse(strJsonInfo, value))
	{
		;
	}
	//string str = value["data"]["flag"].asString();
	
	map<string, string>mp;		//保存 站点编号 和 对应站点中文名字
	int mpNum = value["data"]["map"].size();
	
	//string strTmpFir = value["data"]["map"][ii].asString();
	for(auto sub = value["data"]["map"].begin(); sub != value["data"]["map"].end(); sub++)
	{
		string strFir = sub.memberName();
		string strSec = value["data"]["map"][sub.memberName()].asString();
		mp.insert(pair<string, string>(strFir, strSec));
	}
	
	map<string, string>::iterator mp_it;
	AllTrainNum = value["data"]["result"].size();
	if(ticketInfo != NULL)
	{
		delete []ticketInfo;
		ticketInfo = NULL;
	}
	ticketInfo = new TicketInfo[AllTrainNum] ;//查询一个车次信息时，申请这么多个struct内存
	for(int j = 0; j < AllTrainNum; j++)
	{
		EveryTicketVec.clear();
		string EveryInfo = value["data"]["result"][j].asString();
		EveryTicketVec = SPlit(EveryInfo, "|");
		//if(int m = 0; m < EveryTicketVec.size(); m++)
		//{
			ticketInfo[j].station_train_code	= EveryTicketVec[3];
			//ticketInfo[j].from_station_name	= EveryTicketVec[6];
			//ticketInfo[j].to_station_name		= EveryTicketVec[7];
			for(mp_it = mp.begin(); mp_it != mp.end(); mp_it++)			//把车站编号，换成中文来显示
			{
				if(EveryTicketVec[6] == mp_it->first)
				{
					ticketInfo[j].from_station_name	= mp_it->second;
				}
				if(EveryTicketVec[7] == mp_it->first)
				{
					ticketInfo[j].to_station_name	= mp_it->second;
				}
			}
			ticketInfo[j].start_time			= EveryTicketVec[8];
			ticketInfo[j].arrive_time			= EveryTicketVec[9];
			ticketInfo[j].lishi					= EveryTicketVec[10];
			ticketInfo[j].swz_num				= EveryTicketVec[32];  //商务座 在32或25  后续再调
			ticketInfo[j].zy_num				= EveryTicketVec[31];
			ticketInfo[j].ze_num				= EveryTicketVec[30];
			ticketInfo[j].gr_num				= EveryTicketVec[21];
			ticketInfo[j].rw_num				= EveryTicketVec[23];
			ticketInfo[j].dw_num				= EveryTicketVec[27];
			ticketInfo[j].yw_num				= EveryTicketVec[28];
			ticketInfo[j].rz_num				= EveryTicketVec[24];
			ticketInfo[j].yz_num				= EveryTicketVec[29];
			ticketInfo[j].wz_num				= EveryTicketVec[26];
			ticketInfo[j].qt_num				= EveryTicketVec[22];
		//}
	}
	EveryTicketVec.clear();
	mp.clear();
}
//@bjb|北京北|VAP|beijingbei|bjb|0  一个站名是这种形式

vector<string> EveryStationVec;  
vector<string> OneStationVec;
map<string, string>jianxie1_map;
map<string, string>hanzi_map;
map<string, string>pingyin_map;
map<string, string>jianxie2_map;
map<string, string>xuhao_map;

//split函数  
vector<string> My_SPlit(string str,string separator)
{    
	vector<string> result;  
	result.clear();
	int cutAt;    
	int i = 0;
	while((cutAt = str.find_first_of(separator))!=str.npos)
	{    
		if(cutAt>0)
		{    
			if(i != 0)
			{
				result.push_back(str.substr(0,cutAt));  
			}
		} 
		else if(cutAt == 0)
		{
			result.push_back("-");
		}
		str=str.substr(cutAt+1);    
		i++;
	}    
	if(str.length()>0){    
		result.push_back(str);    
	}    
	return result;    
}  

//解析站点的Json数据
void CWininetHttp::ParseStationJsonInfo(const std::string &strStationJsonInfo)
{
	EveryStationVec.clear();
	jianxie1_map.clear();
	hanzi_map.clear();
	pingyin_map.clear();
	jianxie2_map.clear();
	xuhao_map.clear();
	EveryStationVec = My_SPlit(strStationJsonInfo, "@"); //分离每一个站名的字符串
	
	for(int i = 0; i < EveryStationVec.size(); i++)
	{
		OneStationVec.clear();
		OneStationVec = SPlit(EveryStationVec[i], "|");
		jianxie1_map.insert(pair<string, string>(OneStationVec[0], OneStationVec[2]));
		hanzi_map.insert(pair<string, string>(OneStationVec[1], OneStationVec[2]));
		pingyin_map.insert(pair<string, string>(OneStationVec[3], OneStationVec[2]));
		jianxie2_map.insert(pair<string, string>(OneStationVec[4], OneStationVec[2]));
		xuhao_map.insert(pair<string, string>(OneStationVec[5], OneStationVec[2]));
		OneStationVec.clear();
	}
	//map<string, string>::iterator mp_it;

	//for(mp_it = EveryStationVec.begin(); mp_it != EveryStationVec.end(); mp_it++)
	//{
	//
	//}
}

// 解析URL地址
void CWininetHttp::ParseURLWeb(std::string strUrl, std::string &strHostName, std::string &strPageName, WORD &sPort)
{
	//sPort = 443; //80;
	string strTemp(strUrl);
	int nPos = 0;
	bool isHttps = false;
	nPos = strTemp.find("http://");
	if(nPos == -1)
	{
		nPos = strTemp.find("https://");
		isHttps = true;
	}
	if(nPos != std::string::npos)
	{
		if(isHttps == false)
		{
			strTemp = strTemp.substr(nPos + 7, strTemp.size() - nPos -7);
		}
		else
		{
			strTemp = strTemp.substr(nPos + 8, strTemp.size() - nPos -8);
		}
	}
	nPos = strTemp.find('/');
	if(nPos == std::string::npos)
	{
		strHostName = strTemp;
	}
	else
	{
		strHostName = strTemp.substr(0, nPos);
	}

	std::size_t nPos1 = strHostName.find(':');
	if(nPos1 != std::string::npos)
	{
		std::string strPort = strTemp.substr(nPos1 +1, strHostName.size() - nPos1 -1);
		strHostName = strHostName.substr(0, nPos1);
		sPort = (WORD)atoi(strPort.c_str());
	}
	if(nPos == std::string::npos)
	{
		return ;
	}
	strPageName = strTemp.substr(nPos, strTemp.size() - nPos);
}

// 关闭句柄
void CWininetHttp::Release()
{
	ReleaseHandle(m_hRequest);
	ReleaseHandle(m_hConnect);
	ReleaseHandle(m_hSession);
}

// 释放句柄
void CWininetHttp::ReleaseHandle(HINTERNET & hInternet)
{
	if(hInternet)
	{
		InternetCloseHandle(hInternet);
		hInternet = NULL;
	}
}

char* CWininetHttp::UtfToGbk(const char* utf8)
{
	int len = MultiByteToWideChar(CP_UTF8, 0, utf8, -1, NULL, 0);
	wchar_t* wstr = new wchar_t[len+1];
	memset(wstr, 0, len+1);
	MultiByteToWideChar(CP_UTF8, 0, utf8, -1, wstr, len);
	len = WideCharToMultiByte(CP_ACP, 0, wstr, -1, NULL, 0, NULL, NULL);
	char *str = new char[len+1];
	memset(str, 0, len+1);
	WideCharToMultiByte(CP_ACP, 0, wstr, -1, str, len, NULL, NULL);
	if(wstr)
		delete []wstr;
	return str;
}
