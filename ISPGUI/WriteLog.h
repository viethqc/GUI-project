#pragma once

#define MAX_LOG_LEN				(2 * 1024)					// 2KB		
#define MAX_FILE_LOG_SIZE		(5 * 1024 * 1024)			// 5MB

// Define writelog-mutex name
#define MUTEX_WRITE_LOG			_T("Global\\WriteLogMutex")

#include "afxwin.h"


// Define list of string-log waitting writen
typedef CList<CString, LPCTSTR>	LOG_WAIT_LIST;


class CWriteLog
{
public:
	CWriteLog(void);
	~CWriteLog(void);

private:
	CString			m_sLogPath;
	LOG_WAIT_LIST	m_listLogWaiting;

public:
	HANDLE			m_hWriteLogMutex;

private:
	BOOL IsHaveWaitingLog();
	CString GetWaitingLog();
	void SetWaitingLog(__in LPCTSTR pszWaitLog);

public:
	BOOL InitAll(__in LPCTSTR pszLogPath);
	void WriteLog(__in LPCTSTR pszFormat, ...);
	BOOL WriteToFile(__in LPCTSTR pszData);
};
