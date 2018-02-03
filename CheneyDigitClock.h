#ifndef CHENEY_DIGIT_CLOCK_H
#define CHENEY_DIGIT_CLOCK_H

#pragma once

#include "CheneyWnd.h"

class CheneyDigitClock : public CheneyWnd
{
public:
	CheneyDigitClock(void);
	virtual ~CheneyDigitClock(void);
	virtual BOOL Create(DWORD, CRect, HWND, UINT);
	MESSAGE_HANDLER(Create)
	MESSAGE_HANDLER(Timer)
	MESSAGE_HANDLER(Paint)
	CString str;
	void CheneyStrPaint();
	void CheneyTimer(WPARAM);
protected:
	CImage m_image[12];
};

#endif
