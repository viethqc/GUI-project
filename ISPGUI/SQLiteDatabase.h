#ifndef DATABASE_H
#define DATABASE_H

#include ".\sqlite\sqlite3.h"
#include <stdio.h>
#include <string.h>
#include <Windows.h>
#include <string>

#define MAX_FILE_NAME 1024

using namespace std;

struct SQLiteStmt
{
    sqlite3_stmt * sqliteStmtRes;
    const char * pszTail;
};

class CSQLiteDatabase
{

protected:
    char m_szDatabaseName[MAX_FILE_NAME];
    const char * m_szMsgError;
    sqlite3  * m_psqliteDB;
    SQLiteStmt  m_sqliteStmt;

public:
    CSQLiteDatabase();
    ~CSQLiteDatabase();
    bool Init(char * pszDatabaseName);
    bool Open();
    bool Prepare(SQLiteStmt * sqliteStmt, char * pszSQL);
    bool Prepare(char * pszSQL);
    bool GetNext();
    bool Step();
    bool GetColumnText(char * pszResult, int iBufferResult, int iColumn);
	bool GetColumnText(wchar_t * pszResult, int iBufferResult, int iColumn);
    bool Finalize();
    bool Close();
    bool Execute(char * pszSQL);
	bool Execute(wchar_t * pszSQL);
    const char * GetLastError();
};

#endif // DATABASE_H
