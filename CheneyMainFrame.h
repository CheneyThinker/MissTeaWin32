#ifndef CHENEY_MAIN_FRAME_H
#define CHENEY_MAIN_FRAME_H

#pragma once

#include "CheneyButton.h"
#include "CheneyGragh.h"
#include "CheneyDigitClock.h"
#include "CheneyGraghCtrl.h"
#include "DemoCheneyApp.h"

class CheneyMainFrame : public CheneyWnd
{
public:
	CheneyMainFrame(void);
	virtual ~CheneyMainFrame(void);
	MESSAGE_HANDLER(Close)
	MESSAGE_HANDLER(Destroy)
	MESSAGE_HANDLER(Create)
	MESSAGE_HANDLER(LButtonDown)
	MESSAGE_HANDLER(MouseMove)
	MESSAGE_HANDLER(LButtonUp)
	MESSAGE_HANDLER(Paint)
	MESSAGE_HANDLER(Size)
	MESSAGE_HANDLER(KeyDown)
	MESSAGE_HANDLER(SysKeyDown)
	MESSAGE_HANDLER(KeyUp)
	MESSAGE_HANDLER(SysKeyUp)
	MESSAGE_HANDLER(Char)
	MESSAGE_HANDLER(SysChar)
	MESSAGE_HANDLER(NcPaint)
	MESSAGE_HANDLER(NcActivate)
	MESSAGE_HANDLER(NcMouseMove)
	MESSAGE_HANDLER(NcLButtonDown)
	MESSAGE_HANDLER(NcLButtonUp)
	MESSAGE_HANDLER(NcCalcSize)
	MESSAGE_HANDLER(Command)
	MESSAGE_HANDLER(Notify)
	void CheneyGraghCtrlCreate();
	LRESULT CheneyGraghCtrlSize(WPARAM, LPARAM);
	void CheneyButtonCreate();
	void CheneyGraghLButtonDown(WPARAM, LPARAM);
	void CheneyGraghMouseMove(WPARAM, LPARAM);
	void CheneyGraghLButtonUp();
	void CheneyGraghPaint();
	void CheneyPaint();
	void CheneyMapModePaint();
	void CheneyStrPaint();
	void CheneyDigitClockCreate();
	void CheneyUICreate();
	void CheneyCtrlCreate();
public:
	CString str;
	POINTS curBihua;
	BOOL m_bStart;
	CPoint m_ptOrg;
	CheneyButton m_CheneyButton;
	CheneyGraghCtrl m_CheneyGraghCtrl;
	CheneyDigitClock m_CheneyDigitClock;
	
	CImage m_imgCaption;
	CImage m_imgBorder;
	CImage m_imgCloseBtn;
	CImage m_imgMaxBtn;
	CImage m_imgMinBtn;
	
	// 标准控件
	CheneyWnd m_wndButton;
	CheneyWnd m_wndEdit;
	CheneyWnd m_wndListBox;
	CheneyWnd m_wndScrollBar;
	CheneyWnd m_wndStatic;
	// 通用控件
	CheneyWnd m_wndTreeCtrl;
};

#endif
