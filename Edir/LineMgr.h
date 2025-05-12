#pragma once

#include "Define.h"
#include "Line.h"

class CLineMgr 
{
private:
	CLineMgr();
	~CLineMgr();

public:
	void		Initialize(void);
	void		Update();
	void		Render(HDC hDC);
	void		Release();

	bool		Collision_Line(float _fX,float _fY, float* pX ,float* pY);

	void		Save_Line();
	void		Load_Line();

public:
	static CLineMgr& GetInst()
	{
		static CLineMgr Inst;
		return Inst;
	}

private:
	list<CLine*> m_LineList;
	LINEPOINT m_tLinePoint[END];
};

