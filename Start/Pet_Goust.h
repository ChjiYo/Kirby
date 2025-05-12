#pragma once

#include "Define.h"
#include "Obj.h"

class CPet_Goust :public CObj
{
public:
	CPet_Goust();
	~CPet_Goust();

public:
	void Move();
	void Dir();

public:
	virtual void Initialize();
	virtual int Update();
	virtual void LateUpdate();
	virtual void Render(HDC _hDC);
	virtual void Release();

private:
	float m_fDistance;
	bool m_bMoveStop;
	
	DWORD m_dwMoveTimer;
};

