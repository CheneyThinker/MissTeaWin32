#include "CheneyGraghCtrl.h"

CheneyGraghUnit::CheneyGraghUnit(void)
{
	m_strTitle = _T("");
	m_clrColor = RGB(0x00, 0x00, 0x00);
	m_bVisible = TRUE;
	m_vecData.clear();
}

CheneyGraghUnit::CheneyGraghUnit(const CheneyGraghUnit& gragh)
{
	if(this == &gragh)
		return;
	m_strTitle = gragh.m_strTitle;
	m_clrColor = gragh.m_clrColor;
	m_bVisible = gragh.m_bVisible;
	m_vecData = gragh.m_vecData;
}

CheneyGraghUnit& CheneyGraghUnit::operator=(const CheneyGraghUnit& gragh)
{
	if(this == &gragh)
		return *this;
	m_strTitle = gragh.m_strTitle;
	m_clrColor = gragh.m_clrColor;
	m_bVisible = gragh.m_bVisible;
	m_vecData = gragh.m_vecData;
	return *this;
}

CheneyGraghUnit::~CheneyGraghUnit(void)
{
	m_vecData.clear();
}

void CheneyGraghUnit::SetTitle(CString strTitle)
{
	m_strTitle = strTitle;
}

void CheneyGraghUnit::SetColor(COLORREF clrColor)
{
	m_clrColor = clrColor;
}

void CheneyGraghUnit::SetVisible(BOOL bVisible)
{
	m_bVisible = bVisible;
}

void CheneyGraghUnit::AddData(float x, float y)
{
	CPoint pt;
	pt.x = (LONG) x;
	pt.y = (LONG) y;
	m_vecData.push_back(pt);
}

CString CheneyGraghUnit::GetTitle()
{
	return m_strTitle;
}

COLORREF CheneyGraghUnit::GetColor()
{
	return m_clrColor;
}

BOOL CheneyGraghUnit::IsVisible()
{
	return m_bVisible;
}

vector<CPoint> CheneyGraghUnit::GetData()
{
	return m_vecData;
}

void CheneyGraghUnit::Draw(HDC hDC)
{
	int nDataCount = m_vecData.size();
	if(nDataCount == 0)
		return;
	HPEN hPenGraghColor = CreatePen(PS_SOLID, 20, m_clrColor);
	HPEN hOldPen = (HPEN)SelectObject(hDC, hPenGraghColor);
	if(m_bVisible)
	{
		CPoint pt = m_vecData.at(0);
		MoveToEx(hDC, pt.x, pt.y, NULL);
		for(int i=0; i<nDataCount; i++)
		{
			pt = m_vecData.at(i);
			LineTo(hDC, pt.x, pt.y);
			MoveToEx(hDC, pt.x, pt.y, NULL);
		}
	}
	::SelectObject(hDC, hOldPen);
	DeleteObject(hPenGraghColor);
}

CheneyGraghCtrl::CheneyGraghCtrl()
{
}

CheneyGraghCtrl::~CheneyGraghCtrl()
{
	int nCount = m_vecGragh.size();
	for(int i=0; i<nCount; i++)
	{
		CheneyGraghUnit* pCheneyGraghUnit = (CheneyGraghUnit*)m_vecGragh.at(i);
		if(pCheneyGraghUnit)
		{
			delete pCheneyGraghUnit;
			pCheneyGraghUnit = NULL;
		}
	}
	m_vecGragh.clear();
}

BOOL CheneyGraghCtrl::Create(LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CheneyWnd* pParentWnd, UINT nID)
{
	return CheneyWnd::CreateEx(0, _T("GraghCtrl"), lpszWindowName, dwStyle, rect.left, rect.top, rect.right-rect.left, rect.bottom-rect.top, pParentWnd->m_hWnd, (HMENU)nID);
}

LRESULT CheneyGraghCtrl::OnPaint(WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hDC = ::BeginPaint(m_hWnd, &ps);
	{
		SetBkMode(hDC, TRANSPARENT);
		CRect rcClient;
		GetClientRect(rcClient);
		{
			HBRUSH hBrush = ::CreateSolidBrush(RGB(245, 247, 232));
			::FillRect(hDC, &rcClient, hBrush);
			DeleteObject((HGDIOBJ)hBrush);
		}
		m_rcGragh = rcClient;
		m_rcGragh.DeflateRect(0, 0, 0, 50);
		DrawTip(hDC);
		OnPrepareDC(hDC);
		OnDraw(hDC);
	}
	::EndPaint(m_hWnd, &ps);
	return TRUE;
}

void CheneyGraghCtrl::OnPrepareDC(HDC hDC)
{
	int nRate = 10;
	SetMapMode(hDC, MM_ANISOTROPIC);
	SetViewportExtEx(hDC, m_rcGragh.Width(), m_rcGragh.Height(), NULL);  
	SetViewportOrgEx(hDC, m_rcGragh.Width() / 2, m_rcGragh.Height()/  2, NULL);
	SetWindowExtEx(hDC, m_rcGragh.Width() * nRate, -m_rcGragh.Height() * nRate, NULL);
}

void CheneyGraghCtrl::OnDraw(HDC hDC)
{
	DrawCoodin(hDC);
	DrawGragh(hDC);
}

// 绘制坐标系，采用逻辑坐标来绘制
void CheneyGraghCtrl::DrawCoodin(HDC hDC)
{
	POINT ptLeftTop;
	ptLeftTop.x = m_rcGragh.left;
	ptLeftTop.y = m_rcGragh.top;
	DPtoLP(hDC, &ptLeftTop, 1);
	POINT ptRightBottom;
	ptRightBottom.x = m_rcGragh.right;
	ptRightBottom.y = m_rcGragh.bottom;
	DPtoLP(hDC, &ptRightBottom, 1);
	HPEN hPen = ::CreatePen(PS_SOLID, 0, RGB(135, 135, 135));
	HPEN hOldPen = (HPEN)::SelectObject(hDC, hPen);
	{
		{
			// 画坐标系-横坐标
			MoveToEx(hDC, ptLeftTop.x, 0, NULL);
			LineTo(hDC, ptRightBottom.x, 0);
			// 求逻辑坐标中，X轴显示的最大值
			CString str;
			str.Format(_T("%d"), ptRightBottom.x);
			SIZE szStr;
			GetTextExtentPoint32(hDC, str.GetBuffer(0), str.GetLength(), &szStr);
			TextOut(hDC, ptRightBottom.x-szStr.cx, 0, str.GetBuffer(0), str.GetLength());
		}
		{
			// 画坐标系-横坐标
			MoveToEx(hDC, 0, ptRightBottom.y, NULL);
			LineTo(hDC, 0, ptLeftTop.y);
			// 求逻辑坐标中，X轴显示的最大值
			CString str;
			str.Format(_T("%d"), ptLeftTop.y);
			TextOut(hDC, 0, ptLeftTop.y, str.GetBuffer(0), str.GetLength());
		}
	}
	::SelectObject(hDC, (HGDIOBJ)hOldPen);
}

void CheneyGraghCtrl::DrawGragh(HDC hDC)
{
	int nSize = m_vecGragh.size();
	for(int i=0; i<nSize; i++)
	{
		CheneyGraghUnit* pCheneyGraghUnit = m_vecGragh.at(i);
		pCheneyGraghUnit->Draw(hDC);
	}
}

void CheneyGraghCtrl::AddCheneyGraghUnit(CheneyGraghUnit& gragh)
{
	CheneyGraghUnit* pCheneyGraghUnit = new CheneyGraghUnit(gragh);
	m_vecGragh.push_back(pCheneyGraghUnit);
	InvalidateRect(m_hWnd, NULL, TRUE);
}

void CheneyGraghCtrl::DrawTip(HDC hDC)
{
	m_vecTip.clear();
	int nCount = (int)m_vecGragh.size();
	for(int i = 0; i < nCount; i++)
	{
		CRect rcTip;
		rcTip.left = i * 50;
		rcTip.right = rcTip.left + 50;
		rcTip.top = m_rcGragh.bottom;
		rcTip.bottom = rcTip.top + 50;
		m_vecTip.push_back(rcTip);
		CheneyGraghUnit* pCheneyGraghUnit = (CheneyGraghUnit*)m_vecGragh.at(i);
		HBRUSH hBrush = ::CreateSolidBrush(pCheneyGraghUnit->GetColor());
		FillRect(hDC, rcTip, hBrush);
		DeleteObject((HGDIOBJ)hBrush);
		BOOL bIsVisible = pCheneyGraghUnit->IsVisible();
		if(!bIsVisible)
		{
			MoveToEx(hDC, rcTip.left, rcTip.top, NULL);
			LineTo(hDC, rcTip.right, rcTip.bottom);
			MoveToEx(hDC, rcTip.right, rcTip.top, NULL);
			LineTo(hDC, rcTip.left, rcTip.bottom);
		}
		if(bIsVisible)
		{
			COLORREF clrOldTextColor = SetTextColor(hDC, pCheneyGraghUnit->GetColor());
			COLORREF clrBackColor = SetBkColor(hDC, RGB(0, 255, 0));
			HFONT hFont = CreateFont(
				30						// nHeight
				,0						// nWidth
				,0						// nEscapement
				,0						// nOrientation
				,500						// nWeight
				,FALSE					// nItalic
				,FALSE					// nUnderline
				,0						// cStrikeOut
				,ANSI_CHARSET			// nTCHARSet
				,OUT_DEFAULT_PRECIS	// nOutPrecision
				,CLIP_DEFAULT_PRECIS	// nClipPrecision
				,DEFAULT_QUALITY		// nQuality
				,DEFAULT_PITCH|FF_SWISS// nPitchAndFamily
				,_T("arial"));        // lpszFacename
			HFONT hOldFont = (HFONT)::SelectObject(hDC, (HGDIOBJ)hFont);
			TextOut(hDC, 0, i * 30, pCheneyGraghUnit->GetTitle(), _tcslen(pCheneyGraghUnit->GetTitle()));
			::SelectObject(hDC, (HGDIOBJ)hOldFont);
			DeleteObject((HGDIOBJ)hFont);
			SetBkColor(hDC, clrBackColor);
			SetTextColor(hDC, clrOldTextColor);
		}
	}
}

LRESULT CheneyGraghCtrl::OnLButtonUp(WPARAM wParam, LPARAM lParam)
{
	CPoint pt;
	pt.x = LOWORD(lParam);
	pt.y = HIWORD(lParam);
	int nCount = (int)m_vecTip.size();
	for(int i = 0; i < nCount; i++)
	{
		CRect rcTip = m_vecTip.at(i);
		BOOL bPtInRect = rcTip.PtInRect(pt);
		if(bPtInRect)
		{
			CheneyGraghUnit* pCheneyGraghUnit = (CheneyGraghUnit*)m_vecGragh.at(i);
			BOOL bVisible = pCheneyGraghUnit->IsVisible();
			pCheneyGraghUnit->SetVisible(!bVisible);
			InvalidateRect(m_hWnd, NULL, TRUE);
			break;
		}
	}
	return CheneyWnd::OnLButtonUp(wParam, lParam);
}
