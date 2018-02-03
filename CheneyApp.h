#ifndef CHENEY_APP_H
#define CHENEY_APP_H

#pragma once

#include "stdafx.h"

class CheneyApp
{
public:
	CheneyApp(void);
	~CheneyApp(void);
	virtual BOOL InitInstance();
	virtual BOOL ExitInstance();
	virtual void run();
protected:
	LPVOID m_pCheneyMainWnd;
};

#endif
