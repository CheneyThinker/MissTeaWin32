#ifndef CHENEY_WND_H
#define CHENEY_WND_H

#pragma once

#include "stdafx.h"

class CheneyWnd
{
public:
	CheneyWnd(void);
	virtual ~CheneyWnd(void);
	virtual BOOL PreCreateWindow(CREATESTRUCT&);
	virtual BOOL CreateEx(DWORD, LPCTSTR, LPCTSTR, DWORD, int, int, int, int, HWND, HMENU, LPVOID lpParam = NULL);
	BOOL ShowWindow(int);
	BOOL UpdateWindow();
	BOOL DestroyWindow();
	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
	virtual LRESULT WindowProc(UINT, WPARAM, LPARAM);
	virtual LRESULT Default(UINT, WPARAM, LPARAM);
	BOOL SubClassWindow(HWND);
	static CheneyWnd* FromHandle(HWND);
	BOOL GetClientRect(LPRECT);
	MESSAGE_HANDLERS()
public:
	HWND m_hWnd;
	WNDPROC m_lpfnOldWndProc;
};

#endif
