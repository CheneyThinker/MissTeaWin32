#ifndef DEMO_H
#define DEMO_H

#pragma once

#include "CheneyApp.h"
#include "CheneyGragh.h"

class DemoCheneyApp : public CheneyApp
{
public:
	DemoCheneyApp(void);
	~DemoCheneyApp(void);
	virtual BOOL InitInstance();
	virtual BOOL ExitInstance();
};

extern DemoCheneyApp theApp;
extern CheneyGragh gCheneyGragh;

#endif
