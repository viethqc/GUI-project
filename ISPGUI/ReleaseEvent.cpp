
#include "ReleaseEvent.h"

CReleaseEvent:: CReleaseEvent(bool bReturnValue) : exception()
{
	m_bReturnValue = bReturnValue;
	strWhat = "RELEASE_EVENT";
}

CReleaseEvent::CReleaseEvent(bool bReturnValue, wstring strMsg) : exception()
{
	m_bReturnValue = bReturnValue;
	m_strMsg.clear();
	m_strMsg.append(strMsg);
	strWhat = "RELEASE_EVENT";
}

wstring CReleaseEvent::GetMsg()
{
	return m_strMsg;
}

CReleaseEvent::~ CReleaseEvent()
{

}

bool CReleaseEvent::GetReturn()
{
	return m_bReturnValue;
}

CReleaseEvent::CReleaseEvent()
{
	
}