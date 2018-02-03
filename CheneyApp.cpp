#include "CheneyApp.h"
#include "CheneyGlobal.h"

CheneyApp::CheneyApp(void)
{
	m_pCheneyMainWnd = NULL;
	g_pCheneyApp = this;
}

CheneyApp::~CheneyApp(void)
{
}

BOOL CheneyApp::InitInstance()
{
	return TRUE;
}

BOOL CheneyApp::ExitInstance()
{
	return TRUE;
}

void CheneyApp::run()
{
	MSG msg;
	while(::GetMessage(&msg, NULL, NULL, NULL))
	{
		::TranslateMessage(&msg);
		::DispatchMessage(&msg);
	}
}
