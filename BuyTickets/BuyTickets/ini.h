#pragma once
 
#include "afxTempl.h"

class CIni
{
private:
 CString m_strFileName;
public:
 CIni(CString strFileName):m_strFileName(strFileName)
 {
 }
public:
 //一般性操作：
 BOOL SetFileName(LPCTSTR lpFileName);  //设置文件名
 CString GetFileName(void); //获得文件名
 BOOL SetValue(LPCTSTR lpSection, LPCTSTR lpKey, LPCTSTR lpValue,bool bCreate=true); //设置键值，bCreate是指段名及键名未存在时，是否创建。
 CString GetValue(LPCTSTR lpSection, LPCTSTR lpKey); //得到键值.
 BOOL DelSection(LPCTSTR strSection);  //删除段名
 BOOL DelKey(LPCTSTR lpSection, LPCTSTR lpKey);  //删除键名
 

public:
 //高级操作：
 int GetSections(CStringArray& arrSection);  //枚举出全部的段名
 int GetKeyValues(CStringArray& arrKey,CStringArray& arrValue,LPCTSTR lpSection);  //枚举出一段内的全部键名及值
 
 BOOL DelAllSections();
 
};

