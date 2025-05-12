#pragma once

#include "Define.h"
#include "Monster.h"

class CMonster_Gunter :public CMonster
{
public:
	CMonster_Gunter();
	virtual ~CMonster_Gunter();

public:
	virtual void MotionChage();
	virtual void Initialize();
	virtual int Update();
	virtual void LateUpdate();
	virtual void Render(HDC _hDC);
	virtual void Release();

	virtual void Move();
	void Land();
	void Atttack();

	virtual void SetHp(int m_iDamage) { m_iHp += m_iDamage; }

private:
	float m_fTime;
	int m_iHp;
	float m_iAttackRange;
	float m_fDistance;
	bool m_bMoveStop;
	DWORD m_dwAttackTimer;
	bool m_bAttackStop;

	float m_fMoveRange;
};

