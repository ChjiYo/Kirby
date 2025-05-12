#pragma once

#include "Define.h"
#include "Monster.h"

class CDDDKing : public CMonster
{
public:
	CDDDKing();
	virtual ~CDDDKing();

public:
	void Land();
	void Move();
	
	void AttackA();
	void AttackB();
	void AttackC();

public:
	virtual void SetHp(int m_iDamage) { m_iHp += m_iDamage; }
	virtual int GetHp() { return m_iHp; }

public:
	virtual void MotionChage();
	virtual void Initialize();
	virtual int Update();
	virtual void LateUpdate();
	virtual void Render(HDC _hDC);
	virtual void Release();

private:
	float m_fTime;
	bool m_bMoveStop;
	float m_fDistance;
	DWORD m_dwWaitTimer;

	DWORD m_dwAttackTimerA;
	float m_fAttackRangeA;

	DWORD m_dwAttackTimerB;
	float m_fAttackRangeB;

	DWORD m_dwDeathTimer;
};

