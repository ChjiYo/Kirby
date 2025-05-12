#pragma once

#include "Define.h"
#include "Attack.h"

class CIce:public CAttack
{
public:
	CIce();
	virtual ~CIce();

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
	DWORD m_dwDamageTimer;

};

