#include "CheneyMainFrame.h"

CheneyMainFrame::CheneyMainFrame(void)
{
	str = "";
	m_bStart = FALSE;
	m_CheneyGraghCtrl.m_hWnd = NULL;
	m_CheneyDigitClock.m_hWnd = NULL;
}

CheneyMainFrame::~CheneyMainFrame(void)
{
}

LRESULT CheneyMainFrame::OnClose(WPARAM wParam, LPARAM lParam)
{
	return DestroyWindow();
}

LRESULT CheneyMainFrame::OnDestroy(WPARAM wParam, LPARAM lParam)
{
	PostQuitMessage(0);
	return TRUE;
}

LRESULT CheneyMainFrame::OnCreate(WPARAM wParam, LPARAM lParam)
{
	//CheneyButtonCreate();
	//CheneyGraghCtrlCreate();
	CheneyUICreate();
	//CheneyDigitClockCreate();
	CheneyCtrlCreate();
	return TRUE;
}

LRESULT CheneyMainFrame::OnSize(WPARAM wParam, LPARAM lParam)
{
	return CheneyGraghCtrlSize(wParam, lParam);
}

LRESULT CheneyMainFrame::OnLButtonDown(WPARAM wParam, LPARAM lParam)
{
	CheneyGraghLButtonDown(wParam, lParam);
	return CheneyWnd::OnLButtonDown(wParam, lParam);
}

LRESULT CheneyMainFrame::OnMouseMove(WPARAM wParam, LPARAM lParam)
{
	CheneyGraghMouseMove(wParam, lParam);
	return CheneyWnd::OnMouseMove(wParam, lParam);
}

LRESULT CheneyMainFrame::OnLButtonUp(WPARAM wParam, LPARAM lParam)
{
	CheneyGraghLButtonUp();
	return CheneyWnd::OnLButtonUp(wParam, lParam);
}

LRESULT CheneyMainFrame::OnPaint(WPARAM wParam, LPARAM lParam)
{
	//CheneyGraghPaint();
	//CheneyPaint();
	//CheneyMapModePaint();
	CheneyStrPaint();
	return TRUE;
}

void CheneyMainFrame::CheneyDigitClockCreate()
{
	if(NULL == m_CheneyDigitClock.m_hWnd)
		m_CheneyDigitClock.Create(WS_CHILD | WS_VISIBLE, CRect(0, 0, 160, 60), m_hWnd, IDC_CLOCK);
}

void CheneyMainFrame::CheneyButtonCreate()
{
	if(NULL == m_CheneyButton.m_hWnd)
		m_CheneyButton.CreateEx(_T("www.itxueba.org"), WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 0, 0, 200, 120, m_hWnd, (HMENU)IDC_BUTTON);
}

void CheneyMainFrame::CheneyGraghCtrlCreate()
{
	if(NULL == m_CheneyGraghCtrl.m_hWnd)
	{
		CRect rcClient;
		GetClientRect(rcClient);
		m_CheneyGraghCtrl.Create(_T(""), WS_CHILD | WS_VISIBLE, rcClient, this, IDC_GRAGHCTRL);
		{
			CheneyGraghUnit gragh;
			gragh.SetTitle(_T("正弦曲线"));
			gragh.SetColor(0x0000FF);
			for(int i =- 10000; i < 10000; i++)
			{
				float fX = (float) i;
				float fY = (float) (1000 * sin(2 * 3.1415926 * i / 1000.0f));
				gragh.AddData(fX, fY);
			}
			m_CheneyGraghCtrl.AddCheneyGraghUnit(gragh);
		}
		{
			CheneyGraghUnit gragh;
			gragh.SetTitle(_T("混合曲线"));
			gragh.SetColor(0x00FF00);
			for(int i =- 10000; i < 10000; i++)
			{
				float fX = (float) i;
				float fY = (float) (1000 * sin(2 * 3.1415926 * i / 1000.0f) + 500 * cos(3.1415926 * i / 80.0f));
				gragh.AddData(fX, fY);
			}
			m_CheneyGraghCtrl.AddCheneyGraghUnit(gragh);
		}
		{
			CheneyGraghUnit gragh;
			gragh.SetTitle(_T("圆曲线"));
			gragh.SetColor(0xFF0000);
			for(int i =- 10000; i < 10000; i++)
			{
				float fX = (float) (1000 * cos(2 * 3.1415926 * i / 1000.0f));
				float fY = (float) (1000 * sin(2 * 3.1415926 * i / 1000.0f));
				gragh.AddData(fX, fY);
			}
			m_CheneyGraghCtrl.AddCheneyGraghUnit(gragh);
		}
		{
			CheneyGraghUnit gragh;
			gragh.SetTitle(_T("混合曲线"));
			gragh.SetColor(0x00FFFF);
			for(int i =- 10000; i < 10000; i++)
			{
				float fX = (float) i;
				float fY = (float) (1000 * sin(2 * 3.1415926 * i / 1000.0f) * cos(3.1415926 * i / 99.0f) + 1000);
				gragh.AddData(fX, fY);
			}
			m_CheneyGraghCtrl.AddCheneyGraghUnit(gragh);
		}
		{
			CheneyGraghUnit gragh;
			gragh.SetTitle(_T("混合曲线"));
			gragh.SetColor(0xFFFF00);
			for(int i =- 10000; i < 10000; i++)
			{
				float fX = (float) i;
				float fY = (float) (100000 * 1.0f / i);
				gragh.AddData(fX, fY);
			}
			m_CheneyGraghCtrl.AddCheneyGraghUnit(gragh);
		}
		{
			CheneyGraghUnit gragh;
			gragh.SetTitle(_T("混合曲线"));
			gragh.SetColor(0xFF00FF);
			for(int i =- 10000; i < 10000; i++)
			{
				float fX = (float) i;
				float fY = (float) (0.0001 * i * i);
				gragh.AddData(fX, fY);
			}
			m_CheneyGraghCtrl.AddCheneyGraghUnit(gragh);
		}
	}
}

LRESULT CheneyMainFrame::CheneyGraghCtrlSize(WPARAM wParam, LPARAM lParam)
{
	if(m_CheneyGraghCtrl.m_hWnd)
	{
		CRect rcClient;
		GetClientRect(rcClient);
		::MoveWindow(m_CheneyGraghCtrl.m_hWnd, 0, 0, rcClient.Width(), rcClient.Height(), TRUE);
	}
	return CheneyWnd::Default(WM_SIZE, wParam, lParam);
}

void CheneyMainFrame::CheneyGraghLButtonDown(WPARAM wParam, LPARAM lParam)
{
	SetCapture(m_hWnd);
	m_bStart = TRUE;
	curBihua.clear();
	m_ptOrg.x = LOWORD(lParam);
	m_ptOrg.y = HIWORD(lParam);
	curBihua.push_back(m_ptOrg);
}

void CheneyMainFrame::CheneyGraghMouseMove(WPARAM wParam, LPARAM lParam)
{
	CPoint ptMove;
	ptMove.x = LOWORD(lParam);
	ptMove.y = HIWORD(lParam);
	if(m_bStart)
	{
		HDC hDC = ::GetDC(m_hWnd);
		assert(hDC);
		{
			MoveToEx(hDC, m_ptOrg.x, m_ptOrg.y, NULL);
			LineTo(hDC, ptMove.x, ptMove.y);
			m_ptOrg = ptMove;
		}
		::ReleaseDC(m_hWnd, hDC);
		curBihua.push_back(ptMove);
	}
}

void CheneyMainFrame::CheneyGraghLButtonUp()
{
	ReleaseCapture();
	m_bStart = FALSE;
	gCheneyGragh.AddPoint(curBihua);
}

void CheneyMainFrame::CheneyGraghPaint()
{
	PAINTSTRUCT ps;
	HDC hDC = ::BeginPaint(m_hWnd, &ps);
	assert(hDC);
	gCheneyGragh.Draw(hDC);
	::EndPaint(m_hWnd, &ps);
}

void CheneyMainFrame::CheneyPaint()
{
	RECT rcClient;
	GetClientRect(&rcClient);
	PAINTSTRUCT ps;
	HDC hDC = ::BeginPaint(m_hWnd, &ps);
	assert(hDC);
	{
		/*
		HDC hMemDC = ::CreateCompatibleDC(hDC);
		assert(hMemDC);
		{
			HBITMAP hBitmap = (HBITMAP)::LoadBitmap((HINSTANCE)GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP));
			assert(hBitmap);
			BITMAP bm;
			GetObject((HGDIOBJ)hBitmap, sizeof(BITMAP), &bm);
			{
				HBITMAP hOldBitmap = (HBITMAP)::SelectObject(hMemDC, hBitmap);
				{
					for(int i=0; i<100; i++)
						for(int j=0; j<100; j++)
							::BitBlt(hDC, rcClient.left + bm.bmWidth * i, rcClient.top + bm.bmHeight * j, rcClient.right - rcClient.left, rcClient.bottom - rcClient.top, hMemDC, 0, 0, SRCCOPY);
					//::StretchBlt(hDC, rcClient.left, rcClient.top, rcClient.right-rcClient.left, rcClient.bottom-rcClient.top, hMemDC, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);
				}
				::SelectObject(hMemDC, hOldBitmap);
			}
			::DeleteObject((HGDIOBJ)hBitmap);
		}
		::DeleteDC(hMemDC);
		*/
		
		/*
		// 双缓冲绘图模式
		HDC hMemDC = ::CreateCompatibleDC(hDC);
		assert(hMemDC);
		{
			HBITMAP hCompatibleBitmap = ::CreateCompatibleBitmap(hDC, rcClient.right-rcClient.left, rcClient.bottom-rcClient.top);
 			assert(hCompatibleBitmap);
			{
				HBITMAP hOldBitmap = (HBITMAP)::SelectObject(hMemDC, hCompatibleBitmap);
				{
					HPEN hPen = CreatePen(PS_SOLID, 3, RGB(255,0,0));
					HPEN hOldPen = (HPEN)::SelectObject(hMemDC, (HGDIOBJ)hPen);
					{
						HBRUSH hBrush = CreateSolidBrush(RGB(0,0,255));
						HBRUSH hOldBrush = (HBRUSH)::SelectObject(hMemDC, (HGDIOBJ)hBrush);
						{
							for(int i=0; i<1280; i++)
							{
								for(int j=0; j<800; j++)
								{
									SetPixel(hMemDC, i, j, RGB(0,0,255));
								}
							}
							//::Rectangle(hMemDC, 0, 0, 100, 50);
							//::Ellipse(hDC, 0, 0, 100, 50);
						}
						::SelectObject(hMemDC, (HGDIOBJ)hOldBrush);
						DeleteObject((HGDIOBJ)hOldBrush);
					}
					::SelectObject(hMemDC, (HGDIOBJ)hOldPen);
					::DeleteObject((HGDIOBJ)hPen);

					::BitBlt(hDC, rcClient.left, rcClient.top, rcClient.right-rcClient.left, rcClient.bottom-rcClient.top,
						hMemDC, 0, 0, SRCCOPY);
				}
				::SelectObject(hMemDC, hOldBitmap);
			}
			::DeleteObject((HGDIOBJ)hCompatibleBitmap);
		}
		::DeleteDC(hMemDC);
		*/
		
		/*
		//HPEN hPen = (HPEN)::GetStockObject(NULL_PEN);
		HPEN hPen = CreatePen(PS_SOLID, 3, RGB(255,0,0));
		
		HPEN hOldPen = (HPEN)::SelectObject(hDC, (HGDIOBJ)hPen);
		{
			HBRUSH hBrush = CreateSolidBrush(RGB(0,0,255));
			HBRUSH hOldBrush = (HBRUSH)::SelectObject(hDC, (HGDIOBJ)hBrush);
			{
				::Rectangle(hDC, 0, 0, 100, 50);
				//::Ellipse(hDC, 0, 0, 100, 50);
			}
			::SelectObject(hDC, (HGDIOBJ)hOldBrush);
			DeleteObject((HGDIOBJ)hOldBrush);
		}
		::SelectObject(hDC, (HGDIOBJ)hOldPen);
		::DeleteObject((HGDIOBJ)hPen);
		*/

		/*
		HPEN hPen = CreatePen(PS_DASHDOT, 1, RGB(255,0,0));
		HPEN hOldPen = (HPEN)::SelectObject(hDC, (HGDIOBJ)hPen);
		{
			MoveToEx(hDC, 0, 0, NULL);
			LineTo(hDC, rcClient.right, rcClient.bottom);
		}
		::SelectObject(hDC, (HGDIOBJ)hOldPen);
		DeleteObject((HGDIOBJ)hPen);
		*/
		
		/*
		//输出点
		for(int i=0; i<100; i++)
		{
			for(int j=0; j<100; j++)
			{
				SetPixel(hDC, i, j, RGB(0,0,255));
			}
		}
		*/
		
		/*
		//DrawText(hDC, _T("www.itxueba.org"), _tcslen(_T("www.itxueba.org")), &rcClient, DT_CENTER | DT_VCENTER | DT_WORD_ELLIPSIS | DT_SINGLELINE);
		//DrawText(hDC, _T("www.itxueba.org"), _tcslen(_T("www.itxueba.org")), &rcClient, DT_LEFT|DT_TOP| DT_WORD_ELLIPSIS | DT_SINGLELINE);
		COLORREF clrOldTextColor = SetTextColor(hDC, RGB(255,0,0));
		COLORREF clrBackColor = SetBkColor(hDC, RGB(0,255,0));
		HFONT hFont = CreateFont(
			200						// nHeight
			, 0						// nWidth
			, 0						// nEscapement
			, 0						// nOrientation
			, 500						// nWeight
			, FALSE					// nItalic
			, FALSE					// nUnderline
			, 0						// cStrikeOut
			, ANSI_CHARSET			// nTCHARSet
			, OUT_DEFAULT_PRECIS	// nOutPrecision
			, CLIP_DEFAULT_PRECIS	// nClipPrecision
			, DEFAULT_QUALITY		// nQuality
			, DEFAULT_PITCH|FF_SWISS// nPitchAndFamily
			, _T("arial") );        // lpszFacename
		HFONT hOldFont = (HFONT)::SelectObject(hDC, (HGDIOBJ)hFont);
		{
			//DrawText(hDC, _T("www.itxueba.org"), _tcslen(_T("www.itxueba.org")), &rcClient, DT_LEFT|DT_TOP | DT_SINGLELINE);
			TextOut(hDC, 0, 0,_T("www.itxueba.org"), _tcslen(_T("www.itxueba.org")));
		}
		::SelectObject(hDC, (HGDIOBJ)hOldFont);
		DeleteObject((HGDIOBJ)hFont);

		SetBkColor(hDC, clrBackColor);
		SetTextColor(hDC, clrOldTextColor);
		*/
	}
	::EndPaint(m_hWnd, &ps);
}

void CheneyMainFrame::CheneyMapModePaint()
{
	PAINTSTRUCT ps;
	HDC hDC = ::BeginPaint(m_hWnd, &ps);
	assert(hDC);
	{
		POINT pt;
		pt.x = 20;
		pt.y = 20;
		int nWidth = 0;
		int nHortWidth_PX = GetDeviceCaps(hDC, HORZRES);		// 返回屏幕的像素单位 1280
		int nHortWidth_MM = GetDeviceCaps(hDC, HORZSIZE);		// 返回屏幕的MM毫米单位 320mm  1 ---> 0.25mm
		int nVertWidth_PX = GetDeviceCaps(hDC, VERTRES);		// 返回屏幕的像素单位 800
		int nVertWidth_MM = GetDeviceCaps(hDC, VERTSIZE);		// 返回屏幕的MM毫米单位 200mm
		{
			/*
			MM_LOMETRIC   1个单位 0.1mm
			(1000)	  100mm
			*/
			int nOldMap = SetMapMode(hDC, MM_LOMETRIC);
			nWidth = 1000;
			DPtoLP(hDC, &pt, 1);
			MoveToEx(hDC, pt.x, pt.y, NULL);
			LineTo(hDC, pt.x + nWidth, pt.y);
			TextOut(hDC, pt.x + nWidth, pt.y, _T("MM_LOMETRIC"), _tcslen(_T("MM_LOMETRIC")));
			SetMapMode(hDC, nOldMap);
		}
		{
			/*
			MM_LOMETRIC   1个单位 0.01mm
			(10000)	  100mm
			*/
			pt.x = 20;
			pt.y = 40;
			int nOldMap = SetMapMode(hDC, MM_HIMETRIC);
			nWidth = 10000;
			DPtoLP(hDC, &pt, 1);
			MoveToEx(hDC, pt.x, pt.y, NULL);
			LineTo(hDC, pt.x + nWidth, pt.y);
			TextOut(hDC, pt.x + nWidth, pt.y, _T("MM_HIMETRIC"), _tcslen(_T("MM_HIMETRIC")));
			SetMapMode(hDC, nOldMap);
		}
		{
			/*
			MM_LOMETRIC   1个单位 0.01in (0.01 * 25.4)
			(10000)	  100mm
			*/
			pt.x = 20;
			pt.y = 60;
			int nOldMap = SetMapMode(hDC, MM_LOENGLISH);
			nWidth = (int) (100 * 100 / 25.4);
			DPtoLP(hDC, &pt, 1);
			MoveToEx(hDC, pt.x, pt.y, NULL);
			LineTo(hDC, pt.x + nWidth, pt.y);
			TextOut(hDC, pt.x + nWidth, pt.y, _T("MM_LOENGLISH"), _tcslen(_T("MM_LOENGLISH")));
			SetMapMode(hDC, nOldMap);
		}
		{
			/*
			MM_LOMETRIC   1个单位 0.001in (0.01*25.4)
			(10000)	  100mm
			*/
			pt.x = 20;
			pt.y = 80;
			int nOldMap = SetMapMode(hDC, MM_HIENGLISH);
			nWidth = (int) (1000 * 100 / 25.4);
			DPtoLP(hDC, &pt, 1);
			MoveToEx(hDC, pt.x, pt.y, NULL);
			LineTo(hDC, pt.x + nWidth, pt.y);
			TextOut(hDC, pt.x + nWidth, pt.y, _T("MM_HIENGLISH"), _tcslen(_T("MM_HIENGLISH")));
			SetMapMode(hDC, nOldMap);
		}
		{
			/*
			MM_LOMETRIC   1个单位 1/1440in (1/1440*25.4)
			(10000)	  100mm
			*/
			pt.x = 20;
			pt.y = 100;
			int nOldMap = SetMapMode(hDC, MM_TWIPS);
			nWidth = (int) (1440 * 100 / 25.4);
			DPtoLP(hDC, &pt, 1);
			MoveToEx(hDC, pt.x, pt.y, NULL);
			LineTo(hDC, pt.x + nWidth, pt.y);
			TextOut(hDC, pt.x + nWidth, pt.y, _T("MM_TWIPS"), _tcslen(_T("MM_TWIPS")));
			SetMapMode(hDC, nOldMap);
		}
		{
			/*					1280  320mm
								400	  100
			MM_ANISOTROPIC   1个单位 0.25MM
							(400)	  100mm
			*/
			pt.x = 20;
			pt.y = 120;
			int nOldMap = SetMapMode(hDC, MM_ANISOTROPIC);
			SetViewportExtEx(hDC, 4, 4, NULL);//1280*800  1.25  = 1/8
			SetWindowExtEx(hDC, 1, 1, NULL);//320*200
			nWidth = 100;
			DPtoLP(hDC, &pt, 1);
			MoveToEx(hDC, pt.x, pt.y, NULL);
			LineTo(hDC, pt.x + nWidth, pt.y);
			TextOut(hDC, pt.x + nWidth, pt.y, _T("MM_ANISOTROPIC"), _tcslen(_T("MM_ANISOTROPIC")));
			SetMapMode(hDC, nOldMap);
		}
	}
	::EndPaint(m_hWnd, &ps);
}

void CheneyMainFrame::CheneyStrPaint()
{
	PAINTSTRUCT ps;
	HDC hDC = ::BeginPaint(m_hWnd, &ps);
	assert(hDC);
	{
		CRect rcClient;
		::GetClientRect(m_hWnd, &rcClient);
		::DrawText(hDC, str.GetBuffer(0), str.GetLength(), &rcClient, DT_LEFT | DT_TOP);
	}
	::EndPaint(m_hWnd, &ps);
}

LRESULT CheneyMainFrame::OnKeyDown(WPARAM wParam, LPARAM lParam)
{
	USHORT uState = GetKeyState(VK_CONTROL);
	if((uState & 0x8000)>0)
	{
		if(wParam==VK_F4)
		{
			PostQuitMessage(0);
			return FALSE;
		}
	}
	str = "";
	CString strTemp;
	strTemp.Format(_T("WM_KEYDOWN wParam=%c\r\n"), (TCHAR)wParam);
	str += strTemp;
	InvalidateRect(m_hWnd, NULL, TRUE);
	return CheneyWnd::OnKeyDown(wParam, lParam);
}

LRESULT CheneyMainFrame::OnSysKeyDown(WPARAM wParam, LPARAM lParam)
{
	DWORD dwFlag = lParam & 0x20000000;
	TCHAR chCharCode = (TCHAR) wParam;
	if(chCharCode==VK_F4)
		return FALSE;
	if(wParam==VK_F5)
	{
		PostQuitMessage(0);
		return FALSE;
	}
	str = "";
	CString strTemp;
	strTemp.Format(_T("WM_SYSKEYDOWN wParam=%c\r\n"), (TCHAR)wParam);
	str += strTemp;
	InvalidateRect(m_hWnd, NULL, TRUE);
	return CheneyWnd::OnSysKeyDown(wParam, lParam);
}

LRESULT CheneyMainFrame::OnKeyUp(WPARAM wParam, LPARAM lParam)
{
	CString strTemp;
	strTemp.Format(_T("WM_KEYUP wParam=%c\r\n"), (TCHAR)wParam);
	str += strTemp;
	InvalidateRect(m_hWnd, NULL, TRUE);
	return CheneyWnd::OnKeyUp(wParam, lParam);
}

LRESULT CheneyMainFrame::OnSysKeyUp(WPARAM wParam, LPARAM lParam)
{
	CString strTemp;
	strTemp.Format(_T("WM_SYSKEYUP wParam=%c\r\n"), (TCHAR)wParam);
	str += strTemp;
	InvalidateRect(m_hWnd, NULL, TRUE);
	return CheneyWnd::OnSysKeyUp(wParam, lParam);
}

LRESULT CheneyMainFrame::OnChar(WPARAM wParam, LPARAM lParam)
{
	CString strTemp;
	strTemp.Format(_T("WM_CHAR wParam=%c\r\n"), (TCHAR)wParam);
	str += strTemp;
	InvalidateRect(m_hWnd, NULL, TRUE);
	return CheneyWnd::OnChar(wParam, lParam);
}

LRESULT CheneyMainFrame::OnSysChar(WPARAM wParam, LPARAM lParam)
{
	CString strTemp;
	strTemp.Format(_T("WM_SYSCHAR wParam=%c\r\n"), (TCHAR)wParam);
	str += strTemp;
	InvalidateRect(m_hWnd, NULL, TRUE);
	return CheneyWnd::OnSysChar(wParam, lParam);
}

void CheneyMainFrame::CheneyUICreate()
{
	if(m_imgCaption.IsNull())
		m_imgCaption.LoadFromResource((HINSTANCE)::GetModuleHandle(NULL), IDB_CAPTION);
	if(m_imgBorder.IsNull())
		m_imgBorder.LoadFromResource((HINSTANCE)::GetModuleHandle(NULL), IDB_BORDER);
	if(m_imgCloseBtn.IsNull())
		m_imgCloseBtn.LoadFromResource((HINSTANCE)::GetModuleHandle(NULL), IDB_CLOSEBTN);
	if(m_imgMaxBtn.IsNull())
		m_imgMaxBtn.LoadFromResource((HINSTANCE)::GetModuleHandle(NULL), IDB_MAXBTN);
	if(m_imgMinBtn.IsNull())
		m_imgMinBtn.LoadFromResource((HINSTANCE)::GetModuleHandle(NULL), IDB_MINBTN);
}

LRESULT CheneyMainFrame::OnNcPaint(WPARAM wParam, LPARAM lParam)
{
	if(::IsIconic(m_hWnd))
		return TRUE;
	HDC hDC = ::GetWindowDC(m_hWnd);
	assert(hDC);
	{
		CRect rcWnd;
		GetWindowRect(m_hWnd, &rcWnd);
		CRect rcTitleBar;
		rcTitleBar.left = 0;
		rcTitleBar.right = rcTitleBar.left + rcWnd.Width();
		rcTitleBar.top = 0;
		rcTitleBar.bottom = rcTitleBar.top + TITLEBAR_HEIGHT;
		if(!m_imgCaption.IsNull())
			m_imgCaption.Draw(hDC, rcTitleBar);
		CRect rcLeft;
		rcLeft.left = 0;
		rcLeft.right = rcLeft.left + BORDER_WIDTH;
		rcLeft.top = TITLEBAR_HEIGHT;
		rcLeft.bottom = rcLeft.top + (rcWnd.Height() - TITLEBAR_HEIGHT - BORDER_WIDTH);
		if(!m_imgBorder.IsNull())
			m_imgBorder.Draw(hDC, rcLeft);
		CRect rcRight;
		rcRight.left = rcWnd.Width() - BORDER_WIDTH;
		rcRight.right = rcRight.left + BORDER_WIDTH;
		rcRight.top = TITLEBAR_HEIGHT;
		rcRight.bottom = rcRight.top + (rcWnd.Height() - TITLEBAR_HEIGHT - BORDER_WIDTH);
		if(!m_imgBorder.IsNull())
			m_imgBorder.Draw(hDC, rcRight);
		CRect rcBottom;
		rcBottom.left = 0;
		rcBottom.right = rcWnd.Width();
		rcBottom.top = rcWnd.Height() - BORDER_WIDTH;
		rcBottom.bottom = rcBottom.top + BORDER_WIDTH;
		if(!m_imgBorder.IsNull())
			m_imgBorder.Draw(hDC, rcBottom);
		CRect rcCloseBtn;
		rcCloseBtn.left = rcWnd.Width() - 15 - 4;
		rcCloseBtn.right = rcCloseBtn.left + 15;
		rcCloseBtn.top = 6;
		rcCloseBtn.bottom = rcCloseBtn.top + 15;
		if(!m_imgCloseBtn.IsNull())
			m_imgCloseBtn.Draw(hDC, rcCloseBtn, CRect(0, 0, 15, 15));
		CRect rcMaxBtn;
		rcMaxBtn.left = rcWnd.Width() - 15 - 4 - 15;
		rcMaxBtn.right = rcMaxBtn.left + 15;
		rcMaxBtn.top = 6;
		rcMaxBtn.bottom = rcMaxBtn.top + 15;
		if(!m_imgMaxBtn.IsNull())
			m_imgMaxBtn.Draw(hDC, rcMaxBtn, CRect(0, 0, 15, 15));
		CRect rcMinBtn;
		rcMinBtn.left = rcWnd.Width() - 15 - 4 - 15 - 15;
		rcMinBtn.right = rcMinBtn.left + 15;
		rcMinBtn.top = 6;
		rcMinBtn.bottom = rcMinBtn.top + 15;
		if(!m_imgMinBtn.IsNull())
			m_imgMinBtn.Draw(hDC, rcMinBtn, CRect(0, 0, 15, 15));
	}
	::ReleaseDC(m_hWnd, hDC);
	return TRUE;
}

LRESULT CheneyMainFrame::OnNcActivate(WPARAM wParam, LPARAM lParam)
{
	OnNcPaint(0, 0);
	return 0;
	//return QWnd::OnNcActivate(wParam, lParam);
}

LRESULT CheneyMainFrame::OnNcMouseMove(WPARAM wParam, LPARAM lParam)
{
	CPoint pt;
	pt.x = LOWORD(lParam);
	pt.y = HIWORD(lParam);
	CRect rcWnd;
	GetWindowRect(m_hWnd, &rcWnd);
	HDC hDC = ::GetWindowDC(m_hWnd);
	assert(hDC);
	{
		CRect rcCloseBtn;
		rcCloseBtn.left = rcWnd.right - 15 - 4;
		rcCloseBtn.right = rcCloseBtn.left + 15;
		rcCloseBtn.top = rcWnd.top + 6;
		rcCloseBtn.bottom = rcCloseBtn.top + 15;
		if(rcCloseBtn.PtInRect(pt))
		{
			CRect rcCloseBtn;
			rcCloseBtn.left = rcWnd.Width() - 15 - 4;
			rcCloseBtn.right = rcCloseBtn.left + 15;
			rcCloseBtn.top = 6;
			rcCloseBtn.bottom = rcCloseBtn.top + 15;
			if(!m_imgCloseBtn.IsNull())
				m_imgCloseBtn.Draw(hDC, rcCloseBtn, CRect(15, 0, 30, 15));
		}
		else
		{
			CRect rcCloseBtn;
			rcCloseBtn.left = rcWnd.Width() - 15 - 4;
			rcCloseBtn.right = rcCloseBtn.left + 15;
			rcCloseBtn.top = 6;
			rcCloseBtn.bottom = rcCloseBtn.top + 15;
			if(!m_imgCloseBtn.IsNull())
				m_imgCloseBtn.Draw(hDC, rcCloseBtn, CRect(0, 0, 15, 15));
		}
		CRect rcMaxBtn;
		rcMaxBtn.left = rcWnd.right - 15 - 4 -15;
		rcMaxBtn.right = rcMaxBtn.left + 15;
		rcMaxBtn.top = rcWnd.top + 6;
		rcMaxBtn.bottom = rcMaxBtn.top + 15;
		if(rcMaxBtn.PtInRect(pt))
		{
			CRect rcMaxBtn;
			rcMaxBtn.left = rcWnd.Width() - 15 - 4 - 15;
			rcMaxBtn.right = rcMaxBtn.left + 15;
			rcMaxBtn.top = 6;
			rcMaxBtn.bottom = rcMaxBtn.top + 15;
			if(!m_imgMaxBtn.IsNull())
				m_imgMaxBtn.Draw(hDC, rcMaxBtn, CRect(15, 0, 30, 15));
		}
		else
		{
			CRect rcMaxBtn;
			rcMaxBtn.left = rcWnd.Width() - 15 - 4 - 15;
			rcMaxBtn.right = rcMaxBtn.left + 15;
			rcMaxBtn.top = 6;
			rcMaxBtn.bottom = rcMaxBtn.top + 15;
			if(!m_imgMaxBtn.IsNull())
				m_imgMaxBtn.Draw(hDC, rcMaxBtn, CRect(0, 0, 15, 15));
		}
		CRect rcMinBtn;
		rcMinBtn.left = rcWnd.right - 15 - 4 - 15 - 15;
		rcMinBtn.right = rcMinBtn.left + 15;
		rcMinBtn.top = rcWnd.top + 6;
		rcMinBtn.bottom = rcMinBtn.top + 15;
		if(rcMinBtn.PtInRect(pt))
		{
			CRect rcMinBtn;
			rcMinBtn.left = rcWnd.Width() - 15 - 4 - 15 - 15;
			rcMinBtn.right = rcMinBtn.left + 15;
			rcMinBtn.top = 6;
			rcMinBtn.bottom = rcMinBtn.top + 15;
			if(!m_imgMinBtn.IsNull())
				m_imgMinBtn.Draw(hDC, rcMinBtn, CRect(15, 0, 30, 15));
		}
		else
		{
			CRect rcMinBtn;
			rcMinBtn.left = rcWnd.Width() - 15 - 4 - 15 - 15;
			rcMinBtn.right = rcMinBtn.left + 15;
			rcMinBtn.top = 6;
			rcMinBtn.bottom = rcMinBtn.top + 15;
			if(!m_imgMinBtn.IsNull())
				m_imgMinBtn.Draw(hDC, rcMinBtn, CRect(0, 0, 15, 15));
		}
	}
	::ReleaseDC(m_hWnd, hDC);
	return CheneyWnd::OnNcMouseMove(wParam, lParam);
}

LRESULT CheneyMainFrame::OnNcLButtonDown(WPARAM wParam, LPARAM lParam)
{
	if(wParam == HTCLOSE)
		return TRUE;
	if(wParam == HTMAXBUTTON)
		return TRUE;
	if(wParam == HTMINBUTTON)
		return TRUE;
	return CheneyWnd::OnNcLButtonDown(wParam, lParam);
}

LRESULT CheneyMainFrame::OnNcLButtonUp(WPARAM wParam, LPARAM lParam)
{
	CPoint pt;
	pt.x = LOWORD(lParam);
	pt.y = HIWORD(lParam);
	CRect rcWnd;
	GetWindowRect(m_hWnd, &rcWnd);
	CRect rcCloseBtn;
	rcCloseBtn.left = rcWnd.right - 15 - 4;
	rcCloseBtn.right = rcCloseBtn.left + 15;
	rcCloseBtn.top = rcWnd.top + 6;
	rcCloseBtn.bottom = rcCloseBtn.top + 15;
	if(rcCloseBtn.PtInRect(pt))
	{
		::SendMessage(m_hWnd, WM_SYSCOMMAND, SC_CLOSE, 0);
		return TRUE;
	}
	CRect rcMaxBtn;
	rcMaxBtn.left = rcWnd.right - 15 - 4 -15;
	rcMaxBtn.right = rcMaxBtn.left + 15;
	rcMaxBtn.top = rcWnd.top + 6;
	rcMaxBtn.bottom = rcMaxBtn.top + 15;
	if(rcMaxBtn.PtInRect(pt))
	{
		BOOL bIsZoomed = IsZoomed(m_hWnd);
		if(bIsZoomed)
			::SendMessage(m_hWnd, WM_SYSCOMMAND, SC_RESTORE, 0);
		else
			::SendMessage(m_hWnd, WM_SYSCOMMAND, SC_MAXIMIZE, 0);
		return TRUE;
	}
	CRect rcMinBtn;
	rcMinBtn.left = rcWnd.right - 15 - 4 - 15 - 15;
	rcMinBtn.right = rcMinBtn.left + 15;
	rcMinBtn.top = rcWnd.top + 6;
	rcMinBtn.bottom = rcMinBtn.top + 15;
	if(rcMinBtn.PtInRect(pt))
	{
		::SendMessage(m_hWnd, WM_SYSCOMMAND, SC_MINIMIZE, 0);
		return TRUE;
	}
	return CheneyWnd::OnNcLButtonUp(wParam, lParam);
}

LRESULT CheneyMainFrame::OnNcCalcSize(WPARAM wParam, LPARAM lParam)
{
	if(wParam == TRUE)
	{
		NCCALCSIZE_PARAMS* lpncsp = (NCCALCSIZE_PARAMS*) lParam;
		int iCxBorder = GetSystemMetrics(SM_CXFRAME);
		int iCyBorder = GetSystemMetrics(SM_CYFRAME);
		lpncsp->rgrc[0].left -= iCxBorder;
		lpncsp->rgrc[0].right += iCxBorder;
		lpncsp->rgrc[0].top -= iCyBorder;
		lpncsp->rgrc[0].bottom += iCyBorder;
		lpncsp->rgrc[0].left += 2;
		lpncsp->rgrc[0].right -= 2;
		lpncsp->rgrc[0].top += 2;
		lpncsp->rgrc[0].bottom -= 2;
	}
	return CheneyWnd::OnNcCalcSize(wParam, lParam);
}

void CheneyMainFrame::CheneyCtrlCreate()
{
	//m_wndButton.CreateEx(0, _T("BUTTON"), _T(""), WS_CHILD|WS_VISIBLE|WS_BORDER|BS_DEFPUSHBUTTON, 0, 0, 100, 50, m_hWnd, (HMENU)10001);
	/*m_wndEdit.CreateEx(0, _T("EDIT"), _T(""), WS_CHILD|WS_VISIBLE|WS_BORDER|ES_MULTILINE|WS_VSCROLL|ES_AUTOVSCROLL, 0, 100, 100, 50, m_hWnd, (HMENU)10002);
	m_wndListBox.CreateEx(0, _T("LISTBOX"), _T(""), WS_CHILD|WS_VISIBLE|WS_BORDER|LBS_HASSTRINGS, 0, 200, 100, 50, m_hWnd, (HMENU)10003);
	m_wndScrollBar.CreateEx(0, _T("SCROLLBAR"), _T(""), WS_CHILD|WS_VISIBLE|WS_BORDER|SBS_HORZ , 0, 300, 200, 20, m_hWnd, (HMENU)10004);
	m_wndStatic.CreateEx(0, _T("STATIC"), _T(""), WS_CHILD|WS_VISIBLE, 0, 400, 100, 50, m_hWnd, (HMENU)10005);
	m_wndTreeCtrl.CreateEx(0, WC_TREEVIEW, _T(""), WS_CHILD|WS_VISIBLE|WS_BORDER|TVS_HASLINES|TVS_HASBUTTONS|TVS_LINESATROOT, 0, 500, 200, 200, m_hWnd, (HMENU)10006);
	//m_wndButton.CreateEx(0, _T("BUTTON"), _T(""), WS_CHILD|WS_VISIBLE|WS_BORDER|BS_CHECKBOX, 0, 0, 100, 50, m_hWnd, (HMENU)10001);
	//SendMessage(m_wndButton.m_hWnd, BM_SETCHECK, BST_CHECKED, 0);
	//m_wndEdit.CreateEx(0, _T("EDIT"), _T(""), WS_CHILD|WS_VISIBLE|WS_BORDER|ES_MULTILINE|WS_VSCROLL|ES_AUTOVSCROLL, 0, 100, 100, 50, m_hWnd, (HMENU)10002);
	//SendMessage(m_wndEdit.m_hWnd, WM_SETTEXT, 0, (LPARAM)(_T("www.itxueba.org")));
	//m_wndListBox.CreateEx(0, _T("LISTBOX"), _T(""), WS_CHILD|WS_VISIBLE|WS_BORDER|LBS_HASSTRINGS, 0, 200, 100, 50, m_hWnd, (HMENU)10003);
	//SendMessage(m_wndListBox.m_hWnd, LB_ADDSTRING, 0, (LPARAM)(_T("www.itxueba.org")));
	//SendMessage(m_wndListBox.m_hWnd, LB_ADDSTRING, 0, (LPARAM)(_T("xiaojinyu")));
	//m_wndScrollBar.CreateEx(0, _T("SCROLLBAR"), _T(""), WS_CHILD|WS_VISIBLE|WS_BORDER|SBS_HORZ , 0, 300, 200, 20, m_hWnd, (HMENU)10004);
	//m_wndStatic.CreateEx(0, _T("STATIC"), _T(""), WS_CHILD|WS_VISIBLE, 0, 400, 100, 50, m_hWnd, (HMENU)10005);
	/*m_wndTreeCtrl.CreateEx(0, WC_TREEVIEW, _T(""), WS_CHILD|WS_VISIBLE|WS_BORDER|TVS_HASLINES|TVS_HASBUTTONS|TVS_LINESATROOT, 10, 10, 200, 200, m_hWnd, (HMENU)10006);
	TV_INSERTSTRUCT tvis;
	tvis.hParent = TVI_ROOT;
	tvis.hInsertAfter = TVI_LAST;
	tvis.item.mask = TVIF_TEXT | TVIF_STATE;
	tvis.item.pszText = _T("Windows 程序设计");
	tvis.item.cchTextMax = sizeof(_T("Windows 程序设计"));
	tvis.item.state = TVIS_EXPANDED;
	tvis.item.stateMask = TVIS_EXPANDED;
	HTREEITEM hTreeRoot = (HTREEITEM)::SendMessage(m_wndTreeCtrl.m_hWnd, TVM_INSERTITEM, 0, (LPARAM)(&tvis));
	for(int i = 1; i <= 20; i++)
	{
		tvis.hParent = hTreeRoot;
		CString str;
		str.Format(_T("第%d讲"),  i);
		tvis.item.pszText = str.GetBuffer(0);
		tvis.item.cchTextMax = str.GetLength();
		SendMessage(m_wndTreeCtrl.m_hWnd, TVM_INSERTITEM, 0, (LPARAM)(&tvis));
	}*/

	
	/*m_wndButton.Create(_T(""), WS_CHILD|WS_VISIBLE|WS_BORDER|BS_CHECKBOX, CRect(0, 0, 100, 50), this, 10001);
	//SendMessage(m_wndButton.m_hWnd, BM_SETCHECK, BST_CHECKED, 0);

	m_wndEdit.CreateEx(0, _T("EDIT"), _T(""), WS_CHILD|WS_VISIBLE|WS_BORDER|ES_MULTILINE|WS_VSCROLL|ES_AUTOVSCROLL, 0, 100, 100, 50, m_hWnd, (HMENU)10002);
	SendMessage(m_wndEdit.m_hWnd, WM_SETTEXT, 0, (LPARAM)(_T("www.itxueba.org")));

	m_wndListBox.CreateEx(0, _T("LISTBOX"), _T(""), WS_CHILD|WS_VISIBLE|WS_BORDER|LBS_HASSTRINGS, 0, 200, 100, 50, m_hWnd, (HMENU)10003);
	SendMessage(m_wndListBox.m_hWnd, LB_ADDSTRING, 0, (LPARAM)(_T("www.itxueba.org")));
	SendMessage(m_wndListBox.m_hWnd, LB_ADDSTRING, 0, (LPARAM)(_T("xiaojinyu")));

	m_wndScrollBar.CreateEx(0, _T("SCROLLBAR"), _T(""), WS_CHILD|WS_VISIBLE|WS_BORDER|SBS_HORZ , 0, 300, 200, 20, m_hWnd, (HMENU)10004);
	m_wndStatic.CreateEx(0, _T("STATIC"), _T(""), WS_CHILD|WS_VISIBLE, 0, 400, 100, 50, m_hWnd, (HMENU)10005);

	m_wndTreeCtrl.CreateEx(0, WC_TREEVIEW, _T(""), WS_CHILD|WS_VISIBLE|WS_BORDER|TVS_HASLINES|TVS_HASBUTTONS|TVS_LINESATROOT, 0, 500, 200, 200, m_hWnd, (HMENU)10006);
	TV_INSERTSTRUCT tvis;
	tvis.hParent = TVI_ROOT;
	tvis.hInsertAfter = TVI_LAST;
	tvis.item.mask = TVIF_TEXT | TVIF_STATE;
	tvis.item.pszText = _T("Windows 程序设计");
	tvis.item.cchTextMax = sizeof(_T("Windows 程序设计"));
	tvis.item.state = TVIS_EXPANDED;
	tvis.item.stateMask = TVIS_EXPANDED;
	
	HTREEITEM hTreeRoot = (HTREEITEM)::SendMessage(m_wndTreeCtrl.m_hWnd, TVM_INSERTITEM, 0, (LPARAM)(&tvis));

	for(int i=1; i<=20; i++)
	{
		tvis.hParent = hTreeRoot;
		CString str;
		str.Format(_T("第%d讲"),  i);
		tvis.item.pszText = str.GetBuffer(0);
		tvis.item.cchTextMax = str.GetLength();
		SendMessage(m_wndTreeCtrl.m_hWnd, TVM_INSERTITEM, 0, (LPARAM)(&tvis));
	}*/
}

LRESULT CheneyMainFrame::OnCommand(WPARAM wParam, LPARAM lParam)
{
	UINT idButton = (int)LOWORD(wParam);
	WORD wNotifyCode = HIWORD(wParam);
	HWND hWnd = (HWND) lParam;
	switch(wNotifyCode)
	{
	case BN_CLICKED:
		{
			if(idButton == GetDlgCtrlID(m_wndButton.m_hWnd))
			{
				DWORD dwState = (DWORD)::SendMessage(m_wndButton.m_hWnd, BM_GETCHECK, 0, 0);
				if(dwState == BST_CHECKED)
					//m_wndButton.SetCheck(BST_UNCHECKED);
					SendMessage(m_wndButton.m_hWnd, BM_SETCHECK, BST_UNCHECKED, 0);
				else
					//m_wndButton.SetCheck(BST_CHECKED);
					SendMessage(m_wndButton.m_hWnd, BM_SETCHECK, BST_CHECKED, 0);
			}
		}
		break;
	default:
		break;
	}
	return CheneyWnd::OnCommand(wParam, lParam);
}

LRESULT CheneyMainFrame::OnNotify(WPARAM wParam, LPARAM lParam)
{
	UINT idCtrl = (int) wParam;
	NM_TREEVIEW* pNmtv = (NM_TREEVIEW*) lParam;
	int nCode = pNmtv->hdr.code;
	switch(nCode)
	{
	case TVN_SELCHANGED:
		{
			if(pNmtv->hdr.hwndFrom == m_wndTreeCtrl.m_hWnd)
			{
				HTREEITEM hItemNew = pNmtv->itemNew.hItem;
				TCHAR pszText[1024];
				TVITEM tvi;
				tvi.mask = TVIF_TEXT | TVIF_HANDLE;
				tvi.hItem = hItemNew;
				tvi.pszText = pszText;
				tvi.cchTextMax = 1024;
				::SendMessage(m_wndTreeCtrl.m_hWnd, TVM_GETITEM, 0, (LPARAM)&tvi);
				MessageBox(NULL, pszText, _T(""), 0);
			}
		}
		break;
	default:
		break;
	}
	return CheneyWnd::OnNotify(wParam, lParam);
}
