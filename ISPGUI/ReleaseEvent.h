#ifndef ERROREXCEPTION_H_
#define ERROREXCEPTION_H_

#include <exception>
#include <string>

using namespace std;


#define RETURN(x)	(throw CReleaseEvent(x))
//#define FIRE_RELEASE(bReturnValue, strMsg) (throw CReleaseEvent(bReturnValue, strMsg))
#define NOTIFY()	(throw CReleaseEvent())
#define FIRE_RELEASE(bReturnValue, strMsg) 		throw CReleaseEvent(bReturnValue, strMsg);\
										} catch(exception e) {\
											eptr = std::current_exception();\
										}\
										try\
										{\
											if (eptr)\
											{\
												std::rethrow_exception(eptr);\
											}

class  CReleaseEvent : public exception
{
public:
	CReleaseEvent(bool bReturnValue);
	CReleaseEvent(bool bReturnValue, wstring strMsg);
	CReleaseEvent();
	~CReleaseEvent();
	bool GetReturn();
	wstring GetMsg();

	virtual const char* what() const throw()
	{
		return "RELEASE_EVENT";
	}
private :
	bool m_bReturnValue;
	wstring m_strMsg;
	std::string strWhat;
};

#endif