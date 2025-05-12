#pragma once

#include "Define.h"
#include "Attack.h"

class CGunter_Ice :public CAttack
{
public:
	CGunter_Ice();
	~CGunter_Ice();

public:
	virtual void DamageHit();

public:
	virtual void Initialize();
	virtual int Update();
	virtual void LateUpdate();
	virtual void Render(HDC _hDC);
	virtual void Release();

private:
	DWORD m_dwDamageTimer;
};

