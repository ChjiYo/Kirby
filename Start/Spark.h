#pragma once

#include "Define.h"
#include "Attack.h"

class CSpark :public CAttack
{
public:
	CSpark();
	virtual ~CSpark();

public:
	virtual const int& GetDamage()const { return m_iDamage; }

public:
	virtual void Initialize();
	virtual int Update();
	virtual void LateUpdate();
	virtual void Render(HDC _hDC);
	virtual void Release();

	virtual void DamageHit();

private:
	int m_iScrollX;
	DWORD m_dwDeltaTime;
	float m_fAttackRange;

	DWORD m_dwDamageTimer;
};

