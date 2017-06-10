#include "SQLiteDatabase.h"

// --------------------------------------------------------
// CSQLiteDatabase
// Info:	Constructor
// Params:  none
// Return:	none
// --------------------------------------------------------
CSQLiteDatabase::CSQLiteDatabase()
{
    m_psqliteDB = NULL;
    m_sqliteStmt.sqliteStmtRes = NULL;
    m_sqliteStmt.pszTail = NULL;

    ZeroMemory(m_szDatabaseName, MAX_FILE_NAME);
}

// --------------------------------------------------------
// ~CSQLiteDatabase
// Info:	Destructor
// Params:  none
// Return:	none
// --------------------------------------------------------
CSQLiteDatabase::~CSQLiteDatabase()
{
    Close();
}

// --------------------------------------------------------
// Init
// Info:	Set file name of database
// Params:  __in_   pszDatabaseName : path to sqlite databae file
// Return:	true    : if successful
//			false   : otherwise
// --------------------------------------------------------
bool CSQLiteDatabase::Init(char * pszDatabaseName)
{
    int iLength = -1;

    if (pszDatabaseName == NULL)
    {
        return false;
    }

    iLength = strlen(pszDatabaseName);
    if (iLength >= MAX_FILE_NAME)
    {
        return false;
    }

    strncpy_s(m_szDatabaseName, pszDatabaseName, iLength);
    return true;
}

// --------------------------------------------------------
// Open
// Info:	Open Database
// Params:  none
// Return:	true    : if successful
//			false   : otherwise
// --------------------------------------------------------
bool CSQLiteDatabase::Open()
{
    int iRes;

    if (m_psqliteDB != NULL)
    {
        return false;
    }

    iRes = sqlite3_open(m_szDatabaseName, &m_psqliteDB);
    if (iRes != 0)
    {
        m_szMsgError = sqlite3_errmsg(m_psqliteDB);
        return false;
    }

    return true;
}

// --------------------------------------------------------
// Close
// Info:	Close Database
// Params:  none
// Return:	true    : if successful
//			false   : otherwise
// --------------------------------------------------------
bool CSQLiteDatabase::Close()
{
    if (m_psqliteDB != NULL)
    {
        sqlite3_close(m_psqliteDB);
        m_psqliteDB = NULL;
        return true;
    }
    else
    {
        return false;
    }
}

// --------------------------------------------------------
// Prepare
// Info:	Prepare
// Params:  __out_   sqliteStmt : variable store data
//          __in_   pszSQL      : sql statement
// Return:	true    : if successful
//			false   : otherwise
// --------------------------------------------------------
bool CSQLiteDatabase::Prepare(SQLiteStmt * sqliteStmt, char * pszSQL)
{
    if(m_psqliteDB == NULL)
    {
        return false;
    }

    if(pszSQL == NULL)
    {
        return false;
    }

    if(sqlite3_prepare_v2(m_psqliteDB, pszSQL, strlen(pszSQL), & (* sqliteStmt).sqliteStmtRes, &(* sqliteStmt).pszTail) != SQLITE_OK)
    {
        m_szMsgError = sqlite3_errmsg(m_psqliteDB);
        return false;
    }

    return true;
}

// --------------------------------------------------------
// Prepare
// Info:	Prepare execute sql statement
// Params:  __out_
//          __in_   pszSQL      : sql statement
// Return:	true    : if successful
//			false   : otherwise
// IMPORTANT: if you use Prepare, when not use or not get data, you must call Finalize to release data
// --------------------------------------------------------
bool CSQLiteDatabase::Prepare(char * pszSQL)
{
    if(m_psqliteDB == NULL)
    {
        return false;
    }

    if(pszSQL == NULL)
    {
        return false;
    }

    Finalize();

    if(sqlite3_prepare_v2(m_psqliteDB, pszSQL, strlen(pszSQL), &m_sqliteStmt.sqliteStmtRes, &m_sqliteStmt.pszTail) != SQLITE_OK)
    {
        m_szMsgError = sqlite3_errmsg(m_psqliteDB);
        return false;
    }

    return true;
}

// --------------------------------------------------------
// GetNext
// Info:	goto next row to prepare get data
// Params:  __out_
//          __in_
// Return:	true    : if successful
//			false   : otherwise
// --------------------------------------------------------
bool CSQLiteDatabase::GetNext()
{
    if(m_sqliteStmt.sqliteStmtRes == NULL)
    {
        return false;
    }

    if(sqlite3_step(m_sqliteStmt.sqliteStmtRes) == SQLITE_ROW)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// --------------------------------------------------------
// Step
// Info:	Step
// Params:  __out_
//          __in_
// Return:	true    : if successful
//			false   : otherwise
// --------------------------------------------------------
bool CSQLiteDatabase::Step()
{
    if(m_sqliteStmt.sqliteStmtRes == NULL)
    {
        return false;
    }

    if(sqlite3_step(m_sqliteStmt.sqliteStmtRes) == SQLITE_DONE)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// --------------------------------------------------------
// Execute
// Info:	Execute
// Params:  __out_
//          __in_       pszSQL: SQl statement to execute
// Return:	true    : if successful
//			false   : otherwise
// --------------------------------------------------------
bool CSQLiteDatabase::Execute(char * pszSQL)
{
    int iRes;

    if(pszSQL == NULL)
    {
        return false;
    }

    if(m_psqliteDB == NULL)
    {
        return false;
    }

    iRes = sqlite3_exec(m_psqliteDB, pszSQL, NULL, 0, (char **)&m_szMsgError);
    if(iRes != SQLITE_OK)
    {
        return false;
    }

    return true;
}

// --------------------------------------------------------
// Execute
// Info:	Execute
// Params:  __out_
//          __in_       pszSQL: SQl statement to execute
// Return:	true    : if successful
//			false   : otherwise
// --------------------------------------------------------
bool CSQLiteDatabase::Execute(wchar_t * pszSQL)
{
    int iRes;
	char * szSQL = NULL;

    if(pszSQL == NULL)
    {
        return false;
    }

    if(m_psqliteDB == NULL)
    {
        return false;
    }

	std::wstring wstrSQLite(pszSQL);
	std::string strSQLite(wstrSQLite.begin(), wstrSQLite.end());

    iRes = sqlite3_exec(m_psqliteDB, strSQLite.data(), NULL, 0, (char **)&m_szMsgError);
    if(iRes != SQLITE_OK)
    {
        return false;
    }

    return true;
}

// --------------------------------------------------------
// GetColumnText
// Info:	Get column text
// Params:  __in_   iColumn : column to get data
//          __out_  pszResult : buffer to store data
//                  iBufferResult   : size of buffer out
// Return:	true    : if successful
//			false   : otherwise
// IMPORTANT: if you use Prepare, when not use or not get data, you must call Finalize to release data
// --------------------------------------------------------
bool CSQLiteDatabase::GetColumnText(char * pszResult, int iBufferResult, int iColumn)
{
    char * pszRes = NULL;

    if (m_sqliteStmt.sqliteStmtRes == NULL)
    {
        return false;
    }

    if (iColumn < 0)
    {
        return false;
    }

    pszRes = (char *)sqlite3_column_text(m_sqliteStmt.sqliteStmtRes, iColumn);
    if (pszRes == NULL || strlen(pszRes) > (unsigned int)iBufferResult)
    {
        return false;
    }

    ZeroMemory(pszResult, iBufferResult);
    strncpy_s(pszResult, iBufferResult, pszRes, strlen(pszRes));

    return true;
}

bool CSQLiteDatabase::GetColumnText(wchar_t * pszResult, int iBufferResult, int iColumn)
{

	wchar_t * pszRes = NULL;

	if (m_sqliteStmt.sqliteStmtRes == NULL)
	{
		return false;
	}

	if (iColumn < 0)
	{
		return false;
	}

	pszRes = (wchar_t *)sqlite3_column_text16(m_sqliteStmt.sqliteStmtRes, iColumn);
	if (pszRes == NULL || wcslen(pszRes) > (unsigned int)iBufferResult)
	{
		return false;
	}

	wcsncpy_s(pszResult, iBufferResult, pszRes, wcslen(pszRes));
	pszResult[wcslen(pszRes)] = 0;

	return true;
}

// --------------------------------------------------------
// Finalize
// Info:	Release data after get data
// Params:  none
// Return:	true    : if successful
//			false   : otherwise
// IMPORTANT: if you use Prepare, when not use or not get data, you must call Finalize to release data
// --------------------------------------------------------
bool CSQLiteDatabase::Finalize()
{
    if(m_sqliteStmt.sqliteStmtRes == NULL)
    {
        return false;
    }
    else
    {
        sqlite3_finalize(m_sqliteStmt.sqliteStmtRes);
        m_sqliteStmt.sqliteStmtRes = NULL;
        return true;
    }
}

// --------------------------------------------------------
// GetLastError
// Info:	GetLastError
// Params:  none
// Return:	true    : if successful
//			false   : otherwise
// --------------------------------------------------------
const char * CSQLiteDatabase::GetLastError()
{
    return m_szMsgError;
}
