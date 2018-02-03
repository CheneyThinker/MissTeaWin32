#include "CheneyGragh.h"

CheneyGragh::CheneyGragh(void)
{
}

CheneyGragh::~CheneyGragh(void)
{
}

void CheneyGragh::AddPoint(POINTS point)
{
	vecPoints.push_back(point);
}

void CheneyGragh::Draw(HDC hDC)
{
	int nCount = (int)vecPoints.size();
	for(int i = 0; i < nCount; i++)
	{
		POINTS point = vecPoints.at(i);
		int nPtCount = (int)point.size();
		if(nPtCount > 0)
		{
			CPoint ptOrg = point.at(0);
			MoveToEx(hDC, ptOrg.x, ptOrg.y, NULL);
			for(int j = 0; j < nPtCount; j++)
			{
				CPoint ptMove = point.at(j);
				LineTo(hDC, ptMove.x, ptMove.y);
				MoveToEx(hDC, ptMove.x, ptMove.y, NULL);
			}
		}
	}
}

void CheneyGragh::SetGraghToFile(CString strFileName)
{
	FILE* fp;
	errno_t et = fopen_s(&fp, strFileName.GetBuffer(0), _T("w+b"));
	if(et != 0)
		return;
	int nCount = vecPoints.size();
	fwrite((void*)&nCount, sizeof(int), sizeof(nCount) / sizeof(int), fp);
	for(int i = 0; i < nCount; i++)
	{
		POINTS point = vecPoints.at(i);
		int nPtCount = point.size();
		fwrite((void*)&nPtCount, sizeof(int), sizeof(nPtCount) / sizeof(int), fp);
		if(nPtCount > 0)
		{
			for(int j = 0; j < nPtCount; j++)
			{
				CPoint ptMove = point.at(j);
				fwrite((void*)&ptMove.x, sizeof(ptMove.x), sizeof(ptMove.x) / sizeof(LONG), fp);
				fwrite((void*)&ptMove.y, sizeof(ptMove.y), sizeof(ptMove.y) / sizeof(LONG), fp);
			}
		}
	}
	fclose(fp);
}

void CheneyGragh::GetGraghFromFile(CString strFileName)
{
	vecPoints.clear();
	FILE* fp;
	errno_t et = fopen_s(&fp, strFileName.GetBuffer(0), _T("rb"));
	if(et != 0)
		return;
	int nCount = 0;
	fread((void*)&nCount, sizeof(int), sizeof(nCount) / sizeof(int), fp);
	for(int i = 0; i < nCount; i++)
	{
		POINTS point;
		int nPtCount = 0;
		fread((void*)&nPtCount, sizeof(int), sizeof(nPtCount) / sizeof(int), fp);
		if(nPtCount > 0)
		{
			for(int j = 0; j < nPtCount; j++)
			{
				CPoint ptMove;
				fread((void*)&ptMove.x, sizeof(ptMove.x), sizeof(ptMove.x) / sizeof(LONG), fp);
				fread((void*)&ptMove.y, sizeof(ptMove.y), sizeof(ptMove.y) / sizeof(LONG), fp);
				point.push_back(ptMove);
			}
		}
		AddPoint(point);
	}
	fclose(fp);
}
