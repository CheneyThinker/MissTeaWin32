#include "CheneyButton.h"

CheneyButton::CheneyButton(void)
{
}

CheneyButton::~CheneyButton(void)
{
}

BOOL CheneyButton::CreateEx(LPCTSTR lpszWindowName, DWORD dwStyle, int x, int y, int nWidth, int nHeight, HWND hWndParent, HMENU nIDorHMenu)
{
	return CheneyWnd::CreateEx(0, _T("BUTTON"), lpszWindowName, dwStyle, x, y, nWidth, nHeight, hWndParent, nIDorHMenu);
}

BOOL CheneyButton::Create(LPCTSTR lpszCaption, DWORD dwStyle, const RECT& rect, CheneyWnd* pParentWnd, UINT nID)
{
	CheneyWnd* pCheneyWnd = this;
	return pCheneyWnd->CreateEx(0, _T("BUTTON"), lpszCaption, dwStyle, rect.left, rect.top, rect.right-rect.left, rect.bottom-rect.top, pParentWnd->m_hWnd, (HMENU)nID);
}

void CheneyButton::DrawItem(LPDRAWITEMSTRUCT lpdis)
{
	assert(FALSE);
}

UINT CheneyButton::GetState() const
{
	assert(::IsWindow(m_hWnd));
	return (UINT)::SendMessage(m_hWnd, BM_GETSTATE, 0, 0);
}

void CheneyButton::SetState(BOOL bHighlight)
{
	::SendMessage(m_hWnd, BM_SETSTATE, bHighlight, 0);
}

int CheneyButton::GetCheck() const
{
	assert(::IsWindow(m_hWnd));
	return (int)::SendMessage(m_hWnd, BM_GETCHECK, 0, 0);
}

void CheneyButton::SetCheck(int nCheck)
{
	assert(::IsWindow(m_hWnd));
	::SendMessage(m_hWnd, BM_SETCHECK, nCheck, 0);
}

UINT CheneyButton::GetButtonStyle() const
{
	assert(::IsWindow(m_hWnd));
	return (UINT)GetWindowLong(m_hWnd, GWL_STYLE) & 0xff;
}

void CheneyButton::SetButtonStyle(UINT nStyle, BOOL bRedraw)
{
	assert(::IsWindow(m_hWnd));
	::SendMessage(m_hWnd, BM_SETSTYLE, nStyle, (LPARAM)bRedraw);
}

HICON CheneyButton::SetIcon(HICON hIcon)
{
	assert(::IsWindow(m_hWnd));
	return (HICON)::SendMessage(m_hWnd, BM_SETIMAGE, IMAGE_ICON, (LPARAM)hIcon);
}

HICON CheneyButton::GetIcon() const
{
	assert(::IsWindow(m_hWnd));
	return (HICON)::SendMessage(m_hWnd, BM_GETIMAGE, IMAGE_ICON, 0L);
}

HBITMAP CheneyButton::SetBitmap(HBITMAP hBitmap)
{
	assert(::IsWindow(m_hWnd));
	return (HBITMAP)::SendMessage(m_hWnd, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap);
}

HBITMAP CheneyButton::GetBitmap() const
{
	assert(::IsWindow(m_hWnd));
	return (HBITMAP)::SendMessage(m_hWnd, BM_GETIMAGE, IMAGE_BITMAP, 0L);
}

HCURSOR CheneyButton::SetCursor(HCURSOR hCursor)
{
	assert(::IsWindow(m_hWnd));
	return (HCURSOR)::SendMessage(m_hWnd, BM_SETIMAGE, IMAGE_CURSOR, (LPARAM)hCursor);
}

HCURSOR CheneyButton::GetCursor()
{
	assert(::IsWindow(m_hWnd));
	return (HCURSOR)::SendMessage(m_hWnd, BM_GETIMAGE, IMAGE_CURSOR, 0L);
}
