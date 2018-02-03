#ifndef CHENEY_BUTTON_H
#define CHENEY_BUTTON_H

#pragma once

#include "CheneyWnd.h"

class CheneyButton : public CheneyWnd
{
public:
	CheneyButton(void);
	virtual ~CheneyButton(void);
	virtual BOOL CreateEx(LPCTSTR, DWORD, int, int, int, int, HWND, HMENU);
	virtual BOOL Create(LPCTSTR, DWORD, const RECT&, CheneyWnd*, UINT);
	UINT GetState() const;
	void SetState(BOOL);
	int GetCheck() const;
	void SetCheck(int);
	UINT GetButtonStyle() const;
	void SetButtonStyle(UINT, BOOL bRedraw = TRUE);
	HICON SetIcon(HICON);
	HICON GetIcon() const;
	HBITMAP SetBitmap(HBITMAP);
	HBITMAP GetBitmap() const;
	HCURSOR SetCursor(HCURSOR);
	HCURSOR GetCursor();
#if (_WIN32_WINNT >= 0x501)
	BOOL GetIdealSize(SIZE*);
	BOOL SetImageList(PBUTTON_IMAGELIST);
	BOOL GetImageList(PBUTTON_IMAGELIST);
	BOOL SetTextMargin(RECT*);
	BOOL GetTextMargin(RECT*);
#endif
	virtual void DrawItem(LPDRAWITEMSTRUCT);
};

#endif
