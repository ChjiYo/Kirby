#pragma once

#include "Define.h"
#include "Monster.h"

class CMonster_Sparky :public CMonster
{
public:
	CMonster_Sparky();
	~CMonster_Sparky();

public:
	void Jump();
	virtual void SetHp(int m_iDamage) 
	{
		m_iHp += m_iDamage; 
		int iDebug(0);
	}
public:
	virtual void MotionChage();
	virtual void Initialize();
	virtual int Update();
	virtual void LateUpdate();
	virtual void Render(HDC _hDC);
	virtual void Release();

	virtual void Move();

	virtual void SetState(STATE _eID) { m_eCurState = _eID; }


private:
	float m_fPower;
	float m_fTime;
	bool m_bJump;
	int m_iHp;

	bool m_bInhal;
};

