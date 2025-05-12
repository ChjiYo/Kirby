#pragma once

#include "Define.h"
#include "Attack.h"

class CAirGun :public CAttack
{
public:
	CAirGun();
	virtual ~CAirGun();

public:
	virtual const int& GetDamage()const { return m_iDamage; }

public:
	virtual void Initialize();
	virtual int Update();
	virtual void LateUpdate();
	virtual void Render(HDC _hDC);
	virtual void Release();

	virtual void DamageHit();
};

