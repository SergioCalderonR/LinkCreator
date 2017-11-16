#include <Windows.h>
#include <wchar.h>
#include <objbase.h>
#include <ShObjIdl.h>
#include <ObjIdl.h>

HRESULT CreateLink(LPCWSTR pathObj, LPCWSTR pathLink, LPCWSTR description)
{
	HRESULT hResult;
	IShellLinkW * pShellLink;

	hResult = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLinkW, (LPVOID*)&pShellLink);

	if (SUCCEEDED(hResult))
	{
		IPersistFile* pPersistFile;

		pShellLink->SetPath(pathObj);
		pShellLink->SetDescription(description);
		/*pShellLink->SetArguments(L"\\\\NET-APP01\\ATCFenix");*/

		hResult = pShellLink->QueryInterface(IID_IPersistFile, (LPVOID*)&pPersistFile);

		if (SUCCEEDED(hResult))
		{
			hResult = pPersistFile->Save(pathLink, TRUE);
			pPersistFile->Release();
		}

		pShellLink->Release();		
	}

	return hResult;
}

int wmain(int argc, WCHAR * argv[])
{

	//CreateLink
	LPCWSTR pathObj = L"\\\\NET-APP01\\ATCFenix\\ATCFenixTelco.exe";
	LPCWSTR pathLink = L"C:\\Users\\Public\\Desktop\\ATCFenixUNE.lnk";
	LPCWSTR description = L"FenixATC";
	HRESULT lnkResult;

	////AppData shortcut
	//LPCWSTR pathObjData = L"\\\\epm_po05\\ATCFenix\\ATCFenix.exe";
	//LPCWSTR pathLinkData = L"%AppData%\\Microsoft\\Windows\\Start Menu\\Programs\\Atención Clientes Fenix\\Atención Clientes Fenix.lnk";
	//HRESULT lnkResultData;

	if (CoInitializeEx(NULL, COINIT_MULTITHREADED) != S_OK)
	{
		fwprintf(stderr, L"\nThe COM library was not initialized.\n");
		return FALSE;
	}
	else
	{
		wprintf(L"\nCOM library was initialized successfully.\n");

		//Creating shortcut
		lnkResult = CreateLink(pathObj, pathLink, description);
		

		if (SUCCEEDED(lnkResult))
		{
			wprintf(L"\nShortcut created successfully.\n");

			//Closes the COM library
			CoUninitialize();
		}
		else
		{
			fwprintf(stderr, L"\nShortcut was not created, error: %lu\n", GetLastError());
			return FALSE;
		}


	}	

	return 0;
}