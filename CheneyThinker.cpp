#include "CheneyApp.h"
#include "CheneyGlobal.h"

int WINAPI _tWinMain(IN HINSTANCE hInstance, IN HINSTANCE hPrevInstance, IN LPTSTR lpCmdLine, IN int nShowCmd)
{
	CheneyApp* pCheneyApp = GetCheneyApp();
	assert(pCheneyApp);
	pCheneyApp->InitInstance();
	pCheneyApp->run();
	pCheneyApp->ExitInstance();
	return TRUE;
}