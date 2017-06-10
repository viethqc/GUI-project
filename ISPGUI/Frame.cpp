#include "Frame.h"
#include "SafeDelete.h"
#include "ReleaseEvent.h"
#include "Extractor.h"
 
static RECT wrc = { 0, 0, 800, 800 };  
  
 
CFrame::CFrame() : window( SW_MAIN | SW_ALPHA| SW_ENABLE_DEBUG, wrc)
{  
	this->load( WSTR("this://app/default.htm") ); 
	  
	m_pSQLite = new (std::nothrow) CSQLiteDatabase();
} 

CFrame::~CFrame() 
{
	SAFE_DELETE(m_pSQLite); 
}