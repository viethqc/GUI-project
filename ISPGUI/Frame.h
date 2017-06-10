#ifndef _FRAME_H_
#define _FRAME_H_

#include "WriteLog.h"
#include <atlstr.h> 
#include "sciter-x-window.hpp"
#include "SQLiteDatabase.h"
#include "Shlobj.h"
#include <string>
#include <shellapi.h>
#include "resource.h"
#include <iostream>
#include <fstream>
 
 #pragma comment(lib, "sciter32.lib")

using namespace sciter;
using namespace dom;
using namespace std;
  
class CFrame : public window   
{
public:   
	CFrame();   
	~CFrame(); 
	 
	BEGIN_FUNCTION_MAP    
		//FUNCTION_2("OnClickLoginButton", OnClickLoginButton);
	END_FUNCTION_MAP 
	 
private:
	CSQLiteDatabase *m_pSQLite;
};

#endif 