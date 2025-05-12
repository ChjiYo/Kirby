#pragma once

#include "Define.h"
#include "Attack.h"

class CInhal :public CAttack
{
public:
	CInhal();
	virtual ~CInhal();

public:
	virtual const int& GetDamage()const { return m_iDamage; }

public:
	virtual void Initialize();
	virtual int Update();
	virtual void LateUpdate();
	virtual void Render(HDC _hDC);
	virtual void Release();

	virtual void DamageHit() {};
};

