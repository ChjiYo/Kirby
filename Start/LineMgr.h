#pragma once

#include "Define.h"
#include "Line.h"

class CLineMgr
{
private:
	CLineMgr();
	~CLineMgr();

public:
	bool		Collision_Line(float _fX,float _fY, float* pX,float* pY );
	void		Load_Line();
	void		Load_Stage2();
	void		Load_Stage3();

public:
	static CLineMgr& GetInst()
	{
		static CLineMgr Inst;
		return Inst;
	}

public:
	void Initialize();
	void Render(HDC hDC);
	void Release();

private:
	list<CLine*> m_Linelist;

};

