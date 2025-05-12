#pragma once

#include "Define.h"
#include "Obj.h"

class CAttack :public CObj
{

public:
	CAttack();
	virtual ~CAttack();

public:
	virtual const int& GetDamage()const { return m_iDamage;}
	virtual void SetHp() { m_iHp -= 1; }
	virtual void MotionChange();

public:
	virtual void Initialize();
	virtual int Update();
	virtual void LateUpdate();
	virtual void Render(HDC _hDC);
	virtual void Release();
	
	virtual void DamageHit()		PURE;

protected:
	int m_iDamage;
	int m_iHp;
	int m_iScrollX;
	DWORD m_dwDeltaTime;
	float m_fAttackRange;
};

