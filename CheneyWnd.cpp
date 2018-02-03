#include "CheneyWnd.h"

CheneyWnd::CheneyWnd(void)
{
	m_hWnd = NULL;
	m_lpfnOldWndProc = NULL;
}

CheneyWnd::~CheneyWnd(void)
{
}

BOOL CheneyWnd::SubClassWindow(HWND hWnd)
{
	assert(hWnd);
	if(m_hWnd == hWnd)
		return TRUE;
	m_lpfnOldWndProc = (WNDPROC)GetWindowLong(hWnd, GWL_WNDPROC);
	if(m_lpfnOldWndProc != CheneyWnd::WndProc)
	{
		m_hWnd = hWnd;
		SetWindowLong(m_hWnd, GWL_USERDATA, (LONG)this);
		SetWindowLong(m_hWnd, GWL_WNDPROC, (LONG)CheneyWnd::WndProc);
		return TRUE;
	}
	return FALSE;
}

CheneyWnd* CheneyWnd::FromHandle(HWND hWnd)
{
	assert(hWnd);
	CheneyWnd* pCheneyWnd = (CheneyWnd*)GetWindowLong(hWnd, GWL_USERDATA);
	return pCheneyWnd;
}

BOOL CheneyWnd::PreCreateWindow(CREATESTRUCT& cs)
{
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	BOOL bRet = ::GetClassInfoEx(cs.hInstance, cs.lpszClass, &wcex);
	if(bRet)
		return TRUE;
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = cs.hInstance;
	wcex.hIcon = (HICON)::LoadIcon(NULL, IDI_QUESTION);
	wcex.hIconSm = (HICON)::LoadIcon(NULL, IDI_QUESTION);
	wcex.hbrBackground = (HBRUSH)::GetStockObject(WHITE_BRUSH);
	wcex.hCursor = (HCURSOR)::LoadCursor(NULL, IDC_ARROW);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = cs.lpszClass;
	bRet = ::RegisterClassEx(&wcex);
	if(!bRet)
		return FALSE;
	return TRUE;
}

BOOL CheneyWnd::CreateEx(DWORD dwExStyle, LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, int x, int y, int nWidth, int nHeight, HWND hWndParent, HMENU nIDorHMenu, LPVOID lpParam)
{
	HINSTANCE hInstance = (HINSTANCE)::GetModuleHandle(NULL);
	assert(hInstance);
	CREATESTRUCT cs;
	cs.cx = nWidth;
	cs.cy = nHeight;
	cs.dwExStyle = dwExStyle;
	cs.hInstance = hInstance;
	cs.hMenu = nIDorHMenu;
	cs.hwndParent = hWndParent;
	cs.lpCreateParams = lpParam;
	cs.lpszClass = lpszClassName;
	cs.lpszName = lpszWindowName;
	cs.style = dwStyle;
	cs.x = x;
	cs.y = y;
	BOOL bRet = PreCreateWindow(cs);
	if(!bRet)
	{
		MessageBox(NULL, _T("×¢²á´°¿ÚÀàÊ§°Ü£¡"), _T("×¢²á´°¿ÚÀà"), 0);
		return FALSE;
	}
	HWND hWnd = CreateWindowEx(cs.dwExStyle, cs.lpszClass, cs.lpszName, cs.style, cs.x, cs.y, cs.cx, cs.cy, cs.hwndParent, cs.hMenu, cs.hInstance, this);
	if(NULL == hWnd)
		return FALSE;
	m_hWnd = hWnd;
	SetWindowLong(m_hWnd, GWL_USERDATA, (LONG)this);
	m_lpfnOldWndProc = (WNDPROC)GetWindowLong(m_hWnd, GWL_WNDPROC);
	if(m_lpfnOldWndProc!=CheneyWnd::WndProc)
	{
		SetWindowLong(m_hWnd, GWL_WNDPROC, (LONG)CheneyWnd::WndProc);
		WindowProc(WM_CREATE, 0, 0);
		WindowProc(WM_NCCREATE, 0, 0);
	}
	return TRUE;
}

BOOL CheneyWnd::ShowWindow(int nCmdShow)
{
	assert(m_hWnd);
	return ::ShowWindow(m_hWnd, nCmdShow);
}

BOOL CheneyWnd::UpdateWindow()
{
	assert(m_hWnd);
	return ::UpdateWindow(m_hWnd);
}

BOOL CheneyWnd::DestroyWindow()
{
	assert(m_hWnd);
	return ::DestroyWindow(m_hWnd);
}

BOOL CheneyWnd::GetClientRect(LPRECT lpRect)
{
	assert(m_hWnd);
	return ::GetClientRect(m_hWnd, lpRect);
}

LRESULT CheneyWnd::Default(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if(m_lpfnOldWndProc==CheneyWnd::WndProc)
		return ::DefWindowProc(m_hWnd, uMsg, wParam, lParam);
	return CallWindowProc(m_lpfnOldWndProc, m_hWnd, uMsg, wParam, lParam); 
	//return m_lpfnOldWndProc(m_hWnd, uMsg, wParam, lParam);
}

LRESULT CALLBACK CheneyWnd::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if(uMsg == WM_CREATE || uMsg == WM_NCCREATE)
	{
		LPCREATESTRUCT pCs = (LPCREATESTRUCT)lParam;
		if(pCs)
		{
			CheneyWnd* pWnd = (CheneyWnd*)pCs->lpCreateParams;
			if(pWnd)
			{
				pWnd->m_hWnd = hWnd;
				pWnd->m_lpfnOldWndProc = (WNDPROC)GetWindowLong(hWnd, GWL_WNDPROC);
				return pWnd->WindowProc(uMsg, wParam, lParam);
			}
		}
	}
	CheneyWnd* pWnd = (CheneyWnd*)GetWindowLong(hWnd, GWL_USERDATA);
	if(pWnd)
		return pWnd->WindowProc(uMsg, wParam, lParam);
	return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
}

LRESULT CheneyWnd::WindowProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
		SWITCH_HANDLERS()
		default:
			break;
	}
	return Default(uMsg, wParam, lParam);
}

IMPLEMENT_HANDLERS()
