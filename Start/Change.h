#pragma once

#include "Define.h"
#include "Attack.h"	

class CChange :public CAttack
{
public:
	CChange();
	~CChange();

public:
	virtual void Initialize();
	virtual int Update();
	virtual void LateUpdate();
	virtual void Render(HDC _hDC);
	virtual void Release();

	virtual void DamageHit() {}
};

