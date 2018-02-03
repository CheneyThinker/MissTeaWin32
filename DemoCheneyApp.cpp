#include "DemoCheneyApp.h"
#include "CheneyMainFrame.h"

BOOL CheckFileRelation(const TCHAR* strExt, const TCHAR* strAppKey)
{
	HKEY hExtKey;
	BOOL bRet = RegOpenKey(HKEY_CLASSES_ROOT, _T(".ct"), &hExtKey);
	if(!bRet)
		return FALSE;
	TCHAR szPath[_MAX_PATH];
	DWORD dwSize = sizeof(szPath);
	RegQueryValueEx(hExtKey, NULL, NULL, NULL, (LPBYTE)szPath, &dwSize);
	if(_tcscmp(szPath, strAppKey) == 0)
	{
		RegCloseKey(hExtKey);
		return TRUE;
	}
	RegCloseKey(hExtKey);
	return FALSE;
}

void RegisterFileRelation(TCHAR* strExt, TCHAR* strAppKey, TCHAR* strAppName)
{
	HKEY hKey;
	::RegCreateKey(HKEY_CLASSES_ROOT, strExt, &hKey);
	::RegSetValue(hKey, _T(""), REG_SZ, strAppKey, _tcslen(strAppKey) + 1);
	::RegCloseKey(hKey);
	TCHAR strTemp[_MAX_PATH];
	sprintf_s(strTemp, _T("%s\\shell\\open\\command"), strAppKey);
	::RegCreateKey(HKEY_CLASSES_ROOT, strTemp, &hKey);
	sprintf_s(strTemp, _T("%s \"%%1\""), strAppName);
	::RegSetValue(hKey, _T(""), REG_SZ, strTemp, _tcslen(strTemp) + 1);
	::RegCloseKey(hKey);
}

DemoCheneyApp::DemoCheneyApp(void)
{
}

DemoCheneyApp::~DemoCheneyApp(void)
{
}

DemoCheneyApp theApp;
CheneyGragh gCheneyGragh;

BOOL DemoCheneyApp::InitInstance()
{
	INITCOMMONCONTROLSEX icce;
	icce.dwSize = sizeof(INITCOMMONCONTROLSEX);
	icce.dwICC = ICC_WIN95_CLASSES;
	BOOL bRet = ::InitCommonControlsEx(&icce);
	if(!bRet)
	{
		MessageBox(NULL, _T("初始化通用窗口库失败！"), _T("初始化通用窗口库！"), 0);
		return FALSE;
	}
	BOOL bIsRegester = CheckFileRelation(_T(".ct"), _T("ctfile"));
	if(!bIsRegester)
		RegisterFileRelation(_T(".ct"), _T("ctfile"), _T("C:\\Users\\Chen.Lin\\Documents\\visual studio 2010\\Projects\\CheneyThinkerMFC\\Release\\CheneyThinkerMFC.exe"));
	LPTSTR lpszCommandName = GetCommandLine();
	CString strCommandName = lpszCommandName;
	int nOrder = strCommandName.Find(_T("\" \""));
	if(nOrder >= 0)
	{
		int index = strCommandName.Find("\"", strCommandName.Find("\"", strCommandName.Find("\"", 0) + 1) + 1);
		int finish = strCommandName.Find("\"", index + 1);
		CString strFileName = strCommandName.Mid(index + 1, finish - (index + 1));
		gCheneyGragh.GetGraghFromFile(strFileName.GetBuffer(0));
	}
	CheneyMainFrame* pCheneyMainFrame = new CheneyMainFrame();
	assert(pCheneyMainFrame);
	m_pCheneyMainWnd = pCheneyMainFrame;
	bRet = pCheneyMainFrame->CreateEx(0, _T("CheneyThinker"), _T("CheneyThinker"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL);
	if(!bRet)
	{
		MessageBox(NULL, _T("创建窗口失败！"), _T("创建窗口！"), 0);
		return FALSE;
	}
	pCheneyMainFrame->ShowWindow(SW_SHOW);
	pCheneyMainFrame->UpdateWindow();
	return TRUE;
}

BOOL DemoCheneyApp::ExitInstance()
{
	if(m_pCheneyMainWnd)
	{
		delete (CheneyWnd*)m_pCheneyMainWnd;
		m_pCheneyMainWnd = NULL;
	}
	gCheneyGragh.SetGraghToFile(_T("cheney.ct"));
	return TRUE;
}
