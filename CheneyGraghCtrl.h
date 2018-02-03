#ifndef CHENEY_GRAGH_CTRL_H
#define CHENEY_GRAGH_CTRL_H

#pragma once

#include "CheneyWnd.h"

class CheneyGraghUnit
{
public:
	CheneyGraghUnit(void);
	~CheneyGraghUnit(void);
	CheneyGraghUnit(const CheneyGraghUnit&);
	CheneyGraghUnit& operator=(const CheneyGraghUnit&);
	void SetTitle(CString);
	void SetColor(COLORREF);
	void SetVisible(BOOL);
	void AddData(float, float);
	CString GetTitle();
	COLORREF GetColor();
	BOOL IsVisible();
	vector<CPoint> GetData();
	void Draw(HDC);
private:
	CString m_strTitle;
	COLORREF m_clrColor;
	BOOL m_bVisible;
	vector<CPoint> m_vecData;
};

class CheneyGraghCtrl : public CheneyWnd
{
public:
	CheneyGraghCtrl(void);
	virtual ~CheneyGraghCtrl(void);
	BOOL Create(LPCTSTR, DWORD, const RECT&, CheneyWnd*, UINT);
	void OnPrepareDC(HDC);
	void OnDraw(HDC);
	void DrawGragh(HDC);
	void DrawTip(HDC);
	void DrawCoodin(HDC);
	void AddCheneyGraghUnit(CheneyGraghUnit&);
	vector<CheneyGraghUnit*> m_vecGragh;
	vector<CRect> m_vecTip;
	CRect m_rcGragh;
	MESSAGE_HANDLER(Paint)
	MESSAGE_HANDLER(LButtonUp)
};

#endif
