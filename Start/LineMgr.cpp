#include "LineMgr.h"
#include "ScrollMgr.h"
#include <tchar.h>

CLineMgr::CLineMgr()
{
}

CLineMgr::~CLineMgr()
{
	Release();
}

void CLineMgr::Initialize()
{
	//Stage 1
	/*LINEPOINT		tLinePoint[22]
	{
		{ 0.f, 430.f },
		{ 950.f, 430.f },
		{ 950.f, 380.f },
		{ 1180.f, 380.f },
		{ 1180.f, 430.f },
		{ 1720.f, 430.f },
		{ 1720.f, 380.f },
		{ 1770.f, 380.f },
		{ 1770.f, 430.f },
		{ 2120.f, 430.f },
		{ 2120.f, 380.f },
		{ 2415.f, 380.f },
		
		{ 2415.f, 230.f },
		{ 2600.f, 230.f },
		{ 2900.f, 370.f },
		{ 3600.f, 370.f }, 
		{ 3600.f, 140.f },
		{ 3750.f, 140.f },
		{ 3750.f, 220.f },
		{ 3840.f, 220.f },
		{ 3840.f, 380.f },
		{ 4761.f, 380.f }
	};

	m_Linelist.push_back(new CLine(tLinePoint[0], tLinePoint[1]));
	m_Linelist.push_back(new CLine(tLinePoint[1], tLinePoint[2]));
	m_Linelist.push_back(new CLine(tLinePoint[2], tLinePoint[3]));
	m_Linelist.push_back(new CLine(tLinePoint[3], tLinePoint[4]));
	m_Linelist.push_back(new CLine(tLinePoint[4], tLinePoint[5]));
	m_Linelist.push_back(new CLine(tLinePoint[5], tLinePoint[6]));
	m_Linelist.push_back(new CLine(tLinePoint[6], tLinePoint[7]));
	m_Linelist.push_back(new CLine(tLinePoint[7], tLinePoint[8]));
	m_Linelist.push_back(new CLine(tLinePoint[8], tLinePoint[9]));
	m_Linelist.push_back(new CLine(tLinePoint[9], tLinePoint[10]));
	m_Linelist.push_back(new CLine(tLinePoint[10], tLinePoint[11]));

	m_Linelist.push_back(new CLine(tLinePoint[11], tLinePoint[12]));
	m_Linelist.push_back(new CLine(tLinePoint[12], tLinePoint[13]));
	m_Linelist.push_back(new CLine(tLinePoint[13], tLinePoint[14]));
	m_Linelist.push_back(new CLine(tLinePoint[14], tLinePoint[15]));
	m_Linelist.push_back(new CLine(tLinePoint[15], tLinePoint[16]));
	m_Linelist.push_back(new CLine(tLinePoint[16], tLinePoint[17]));
	m_Linelist.push_back(new CLine(tLinePoint[17], tLinePoint[18]));
	m_Linelist.push_back(new CLine(tLinePoint[18], tLinePoint[19]));
	m_Linelist.push_back(new CLine(tLinePoint[19], tLinePoint[20]));
	m_Linelist.push_back(new CLine(tLinePoint[20], tLinePoint[21]));*/

	/*LINEPOINT		tLinePoint[18]
	{
		{ 0.f, 480.f },
		{ 600.f, 480.f },
		{ 840.f, 350.f },
		{ 1275.f, 350.f },
		{ 1500.f, 480.f },
		{ 2130.f, 480.f },
		{ 2255.f, 352.f },
		{ 2460.f, 250.f },
		{ 2550.f, 250.f },
		{ 2550.f, 430.f },
		{ 2830.f, 430.f },
		{ 2830.f, 250.f },
		{ 2950.f, 250.f },
		{ 3140.f, 370.f },
		{ 3240.f, 470.f },
		{ 4330.f, 470.f },
		{ 4450.f, 370.f },
		{ 4761, 370.f },
	};

	LINEPOINT		tLineObjectA[6]
	{
		{997 , 0},
		{997 ,270},
		{1028, 310},
		{1100, 310},
		{1135,  270},
		{1135,  0},
	};

	LINEPOINT		tLineObjectB[4]
	{
		{3825 ,160},
		{3825 ,360},
		{3900, 360},
		{3900, 160},
	};

	m_Linelist.push_back(new CLine(tLinePoint[0], tLinePoint[1]));
	m_Linelist.push_back(new CLine(tLinePoint[1], tLinePoint[2]));
	m_Linelist.push_back(new CLine(tLinePoint[2], tLinePoint[3]));
	m_Linelist.push_back(new CLine(tLinePoint[3], tLinePoint[4]));
	m_Linelist.push_back(new CLine(tLinePoint[4], tLinePoint[5]));
	m_Linelist.push_back(new CLine(tLinePoint[5], tLinePoint[6]));
	m_Linelist.push_back(new CLine(tLinePoint[6], tLinePoint[7]));
	m_Linelist.push_back(new CLine(tLinePoint[7], tLinePoint[8]));
	m_Linelist.push_back(new CLine(tLinePoint[8], tLinePoint[9]));
	m_Linelist.push_back(new CLine(tLinePoint[9], tLinePoint[10]));
	m_Linelist.push_back(new CLine(tLinePoint[10], tLinePoint[11]));
	m_Linelist.push_back(new CLine(tLinePoint[11], tLinePoint[12]));
	m_Linelist.push_back(new CLine(tLinePoint[12], tLinePoint[13]));
	m_Linelist.push_back(new CLine(tLinePoint[13], tLinePoint[14]));
	m_Linelist.push_back(new CLine(tLinePoint[14], tLinePoint[15]));
	m_Linelist.push_back(new CLine(tLinePoint[15], tLinePoint[16]));
	m_Linelist.push_back(new CLine(tLinePoint[16], tLinePoint[17]));

	m_Linelist.push_back(new CLine(tLineObjectA[0], tLineObjectA[1]));
	m_Linelist.push_back(new CLine(tLineObjectA[1], tLineObjectA[2]));
	m_Linelist.push_back(new CLine(tLineObjectA[2], tLineObjectA[3]));
	m_Linelist.push_back(new CLine(tLineObjectA[3], tLineObjectA[4]));
	m_Linelist.push_back(new CLine(tLineObjectA[4], tLineObjectA[5]));
	
	m_Linelist.push_back(new CLine(tLineObjectB[0], tLineObjectB[1]));
	m_Linelist.push_back(new CLine(tLineObjectB[1], tLineObjectB[2]));
	m_Linelist.push_back(new CLine(tLineObjectB[2], tLineObjectB[3]));
	m_Linelist.push_back(new CLine(tLineObjectB[3], tLineObjectB[0]));*/

	/*LINEPOINT		tLinePoint[16]
	{
		{ 0.f, 415.f },
		{ 700, 415.f },
		{ 700.f, 360.f },
		{ 1530.f, 360.f },
		{ 1710.f, 270.f },
		{ 1870.f, 270.f },
		{ 1870.f, 500.f },
		{ 2500.f, 500.f },
		{ 2500.f, 270.f },
		{ 2640.f, 270.f },
		{ 2850.f, 360.f },
		{ 2930.f, 360.f },
		{ 3150.f, 490.f },
		{ 3970.f, 490.f },
		{ 3970.f, 210.f },
		{ 4761.f, 210.f },
	};

	LINEPOINT		tLineObjectA[2]
	{
		{400 , 165},
		{700 ,165},
	
	};

	LINEPOINT		tLineObjectB[2]
	{
		{2950,165},
		{3300 ,165},
	
	};

	LINEPOINT		tLineObjectC[2]
	{
		{3830,220},
		{3970 ,220},

	};

	m_Linelist.push_back(new CLine(tLinePoint[0], tLinePoint[1]));
	m_Linelist.push_back(new CLine(tLinePoint[1], tLinePoint[2]));
	m_Linelist.push_back(new CLine(tLinePoint[2], tLinePoint[3]));
	m_Linelist.push_back(new CLine(tLinePoint[3], tLinePoint[4]));
	m_Linelist.push_back(new CLine(tLinePoint[4], tLinePoint[5]));
	m_Linelist.push_back(new CLine(tLinePoint[5], tLinePoint[6]));
	m_Linelist.push_back(new CLine(tLinePoint[6], tLinePoint[7]));
	m_Linelist.push_back(new CLine(tLinePoint[7], tLinePoint[8]));
	m_Linelist.push_back(new CLine(tLinePoint[8], tLinePoint[9]));
	m_Linelist.push_back(new CLine(tLinePoint[9], tLinePoint[10]));
	m_Linelist.push_back(new CLine(tLinePoint[10], tLinePoint[11]));
	m_Linelist.push_back(new CLine(tLinePoint[11], tLinePoint[12]));
	m_Linelist.push_back(new CLine(tLinePoint[12], tLinePoint[13]));
	m_Linelist.push_back(new CLine(tLinePoint[13], tLinePoint[14]));
	m_Linelist.push_back(new CLine(tLinePoint[14], tLinePoint[15]));

	m_Linelist.push_back(new CLine(tLineObjectA[0], tLineObjectA[1]));

	m_Linelist.push_back(new CLine(tLineObjectB[0], tLineObjectB[1]));

	m_Linelist.push_back(new CLine(tLineObjectC[0], tLineObjectC[1]));*/

	LINEPOINT		tLinePoint[22]
	{
		{ 0.f, 450.f },
		{ 1550.f, 450.f },
		{ 1550.f, 0.f },
	};

	LINEPOINT		tLineObjectA[22]
	{
		{ 0.f, 200.f },
		{ 200.f, 200.f },
		
	};

	LINEPOINT		tLineObjectB[22]
	{
		{ 600.f, 200.f },
		{ 800.f, 200.f },
	};

	m_Linelist.push_back(new CLine(tLinePoint[0], tLinePoint[1]));
	m_Linelist.push_back(new CLine(tLinePoint[1], tLinePoint[2]));
	m_Linelist.push_back(new CLine(tLinePoint[2], tLinePoint[3]));

	m_Linelist.push_back(new CLine(tLineObjectA[0], tLineObjectA[1]));
	m_Linelist.push_back(new CLine(tLineObjectA[1], tLineObjectA[2]));

	m_Linelist.push_back(new CLine(tLineObjectB[0], tLineObjectB[1]));
	m_Linelist.push_back(new CLine(tLineObjectB[1], tLineObjectB[2]));

}

void CLineMgr::Render(HDC hDC)
{
	for (auto& iter : m_Linelist)
		iter->Render(hDC);
}

void CLineMgr::Release()
{
	for_each(m_Linelist.begin(), m_Linelist.end(), Safe_Delete<CLine*>);
	m_Linelist.clear();
}

bool CLineMgr::Collision_Line(float _fX, float _fY, float* pX, float* pY)
{
	if (m_Linelist.empty())
		return false;

	CLine* pTarget = nullptr;

	for (auto& iter : m_Linelist)
	{
		if (iter->GetInfo().tLeft.fX <= _fX &&
			iter->GetInfo().tRight.fX > _fX && (iter->GetInfo().tLeft.fY >= _fY || iter->GetInfo().tRight.fY >= _fY))
		{
			pTarget = iter;
		}
	}

	if (!pTarget)
		return false;

	float x1 = pTarget->GetInfo().tLeft.fX;
	float x2 = pTarget->GetInfo().tRight.fX;
	float y1 = pTarget->GetInfo().tLeft.fY;
	float y2 = pTarget->GetInfo().tRight.fY;

	*pX = ((x2 - x1) / (y2 - y1)) * (_fY - y1) + x1;
	*pY = ((y2 - y1) / (x2 - x1)) * (_fX - x1) + y1;

	return true;
}

void CLineMgr::Load_Line()
{
	HANDLE	hFile = CreateFile(L"../Stage/Stage1.dat", 
		GENERIC_READ,		
		NULL,		
		NULL,				
		OPEN_EXISTING,		
		FILE_ATTRIBUTE_NORMAL,	
		NULL);				

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, _T("Load File"), L"Fail", MB_OK);
		return;
	}

	DWORD	dwByte(0);

	LINEINFO		tInfo{};

	while (true)
	{
		ReadFile(hFile, &tInfo, sizeof(LINEINFO), &dwByte, NULL);

		if (0 == dwByte)
			break;

		m_Linelist.push_back(new CLine(tInfo));
	}

	CloseHandle(hFile);

	//MessageBox(g_hWnd, _T("Load 완료"), L"성공", MB_OK);
}

void CLineMgr::Load_Stage2()
{
	HANDLE	hFile = CreateFile(L"../Stage/Stage2.dat",
		GENERIC_READ,
		NULL,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, _T("Load File"), L"Fail", MB_OK);
		return;
	}

	DWORD	dwByte(0);

	LINEINFO		tInfo{};

	while (true)
	{
		ReadFile(hFile, &tInfo, sizeof(LINEINFO), &dwByte, NULL);

		if (0 == dwByte)
			break;

		m_Linelist.push_back(new CLine(tInfo));
	}

	CloseHandle(hFile);

	//MessageBox(g_hWnd, _T("Load 완료"), L"성공", MB_OK);
}

void CLineMgr::Load_Stage3()
{
	HANDLE	hFile = CreateFile(L"../Stage/Stage3.dat",
		GENERIC_READ,
		NULL,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, _T("Load File"), L"Fail", MB_OK);
		return;
	}

	DWORD	dwByte(0);

	LINEINFO		tInfo{};

	while (true)
	{
		ReadFile(hFile, &tInfo, sizeof(LINEINFO), &dwByte, NULL);

		if (0 == dwByte)
			break;

		m_Linelist.push_back(new CLine(tInfo));
	}

	CloseHandle(hFile);

	//MessageBox(g_hWnd, _T("Load 완료"), L"성공", MB_OK);
}