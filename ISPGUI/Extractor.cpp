#include "Extractor.h"

bool ExtractSingleResource(DWORD dwID, CString strName, CString strFileName)
{
	HRSRC	hRes				= NULL;
	HGLOBAL	hGlobal				= NULL;
	HANDLE	hFile				= INVALID_HANDLE_VALUE;
	DWORD	dwSizeResource		= 0;
	DWORD	dwNumberByteWritten = 0;
	BYTE *	pbData				= NULL;

	try
	{
		hRes = FindResource(NULL, MAKEINTRESOURCE(dwID), strName.GetBuffer());
		if (hRes == NULL)
		{
			return false;
		}

		hGlobal = LoadResource(NULL, hRes);
		if (hGlobal == NULL)
		{
			return false;
		}

		dwSizeResource = SizeofResource(NULL, hRes);
		if (dwSizeResource == 0)
		{
			RETURN(false);
		}

		pbData = (BYTE *)LockResource(hGlobal);
		if (pbData == NULL)
		{
			RETURN(false);
		}

		hFile = CreateFile(strFileName.GetBuffer(), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		if (hFile == INVALID_HANDLE_VALUE)
		{
			RETURN(false);
		}

		if (WriteFile(hFile, pbData, dwSizeResource, &dwNumberByteWritten, NULL) == false)
		{
			RETURN(false);
		}

		if (dwSizeResource != dwNumberByteWritten)
		{
			RETURN(false);
		}

		RETURN(true);
	}
	catch (CReleaseEvent e)
	{
		if (hGlobal != NULL)
		{
			FreeResource(hGlobal);
		}

		if (hFile != INVALID_HANDLE_VALUE)
		{
			CloseHandle(hFile);
		}

		return e.GetReturn();
	}
}