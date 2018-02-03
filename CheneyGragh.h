#ifndef CHENEY_GRAGH_H
#define CHENEY_GRAGH_H

#pragma once

#include "stdafx.h"

#define POINTS vector<CPoint>

class CheneyGragh
{
public:
	CheneyGragh(void);
	virtual ~CheneyGragh(void);
	void SetGraghToFile(CString);
	void GetGraghFromFile(CString);
	void AddPoint(POINTS);
	virtual void Draw(HDC);
private:
	vector<POINTS> vecPoints;
};

#endif
