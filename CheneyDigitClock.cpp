#include "CheneyDigitClock.h"

CheneyDigitClock::CheneyDigitClock(void)
{
	SYSTEMTIME st;
	GetLocalTime(&st);
	str.Format(_T("%04d-%02d-%02d %02d:%02d:%02d"), st.wYear, st.wMonth, st.wDay, st.wMonth, st.wMinute, st.wSecond);
}

CheneyDigitClock::~CheneyDigitClock(void)
{
}

LRESULT CheneyDigitClock::OnCreate(WPARAM wParam, LPARAM lParam)
{
	for(int i = 0; i < 12; i++)
		m_image[i].LoadFromResource((HINSTANCE)::GetModuleHandle(NULL), IDB_CLOCK0 + i);
	SetTimer(m_hWnd, ID_TIMER, 500, NULL);
	//SetTimer(m_hWnd, ID_TIMER, 500, TimerProc);
	return TRUE;
}

BOOL CheneyDigitClock::Create(DWORD dwStyle, CRect rc, HWND hWndParent, UINT uID)
{
	return CheneyWnd::CreateEx(0, _T("DIGITCLOCK"), "", dwStyle, rc.left, rc.top, rc.Width(), rc.Height(), hWndParent, (HMENU)uID);
}

LRESULT CheneyDigitClock::OnTimer(WPARAM wParam, LPARAM lParam)
{
	//CheneyTimer(wParam);
	InvalidateRect(m_hWnd, NULL, FALSE);
	return CheneyWnd::OnTimer(wParam, lParam);
}

LRESULT CheneyDigitClock::OnPaint(WPARAM wParam, LPARAM lParam)
{
	//CheneyStrPaint();
	PAINTSTRUCT ps;
	HDC hDC = ::BeginPaint(m_hWnd, &ps);
	assert(hDC);
	{
		SYSTEMTIME st;
		GetLocalTime(&st);
		int nHiHour = st.wHour / 10;
		int nLoHour = st.wHour % 10;
		int nHiMinute = st.wMinute / 10;
		int nLoMinute = st.wMinute % 10;
		int nHiSecond = st.wSecond / 10;
		int nLoSecond = st.wSecond % 10;
		CRect rcClient;
		::GetClientRect(m_hWnd, &rcClient);
		if(!m_image[nHiHour].IsNull())
			m_image[nHiHour].Draw(hDC, CRect(rcClient.Width() * 0 / 8, 0, rcClient.Width() * 1 / 8, rcClient.Height()));
		if(!m_image[nLoHour].IsNull())
			m_image[nLoHour].Draw(hDC, CRect(rcClient.Width() * 1 / 8, 0, rcClient.Width() * 2 / 8, rcClient.Height()));
		static BOOL bRet = FALSE;
		if(bRet)
		{
			if(!m_image[11].IsNull())
			{
				m_image[11].Draw(hDC, CRect(rcClient.Width() * 2 / 8, 0, rcClient.Width() * 3 / 8, rcClient.Height()));
				m_image[11].Draw(hDC, CRect(rcClient.Width() * 5 / 8, 0, rcClient.Width() * 6 / 8, rcClient.Height()));
			}
			bRet = FALSE;
		}
		else
		{
			if(!m_image[10].IsNull())
			{
				m_image[10].Draw(hDC, CRect(rcClient.Width() * 2 / 8, 0, rcClient.Width() * 3 / 8, rcClient.Height()));
				m_image[10].Draw(hDC, CRect(rcClient.Width() * 5 / 8, 0, rcClient.Width() * 6 / 8, rcClient.Height()));
			}
			bRet = TRUE;
		}
		if(!m_image[nHiMinute].IsNull())
			m_image[nHiMinute].Draw(hDC, CRect(rcClient.Width() * 3 / 8, 0, rcClient.Width() * 4 / 8, rcClient.Height()));
		if(!m_image[nLoMinute].IsNull())
			m_image[nLoMinute].Draw(hDC, CRect(rcClient.Width() * 4 / 8, 0, rcClient.Width() * 5 / 8, rcClient.Height()));
		if(!m_image[nHiSecond].IsNull())
			m_image[nHiSecond].Draw(hDC, CRect(rcClient.Width() * 6 / 8, 0, rcClient.Width() * 7 / 8, rcClient.Height()));
		if(!m_image[nLoSecond].IsNull())
			m_image[nLoSecond].Draw(hDC, CRect(rcClient.Width() * 7 / 8, 0, rcClient.Width() * 8 / 8, rcClient.Height()));
	}
	::EndPaint(m_hWnd, &ps);
	return TRUE;
}

void  CheneyDigitClock::CheneyTimer(WPARAM wParam)
{
	if(wParam == ID_TIMER)
	{
		SYSTEMTIME st;
		GetLocalTime(&st);
		str.Format(_T("%04d-%02d-%02d %02d:%02d:%02d"), st.wYear, st.wMonth, st.wDay, st.wMonth, st.wMinute, st.wSecond);
		InvalidateRect(m_hWnd, NULL, TRUE);
	}
}

void  CheneyDigitClock::CheneyStrPaint()
{
	PAINTSTRUCT ps;
	HDC hDC = ::BeginPaint(m_hWnd, &ps);
	assert(hDC);
	{
		CRect rcClient;
		::GetClientRect(m_hWnd, &rcClient);
		::DrawText(hDC, str.GetBuffer(0), str.GetLength(), &rcClient, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	}
	::EndPaint(m_hWnd, &ps);
}

void CALLBACK TimerProc(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
	assert(hWnd);
	CheneyDigitClock* pCheneyDigitClock = (CheneyDigitClock*)CheneyWnd::FromHandle(hWnd);
	CString& str = pCheneyDigitClock->str;
	if(idEvent == ID_TIMER)
	{
		SYSTEMTIME st;
		GetLocalTime(&st);
		str.Format(_T("%04d-%02d-%02d %02d:%02d:%02d"), st.wYear, st.wMonth, st.wDay, st.wMonth, st.wMinute, st.wSecond);
		InvalidateRect(hWnd, NULL, TRUE);
	}
}
