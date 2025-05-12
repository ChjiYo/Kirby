#pragma once

#include "Define.h"
#include "Monster.h"

class CWadle :public CMonster
{
public:
	CWadle();
	~CWadle();

public:
	virtual void SetHp(int m_iDamage) { m_iHp += m_iDamage; }
	virtual void Move();
	virtual void KillCount() { m_iKillCount++; }
	void Land();
	void MotionChage();

public:
	void Initialize();
	int Update();
	void LateUpdate();
	void Render(HDC _hDC);
	void Release();

private:
	float m_fMoveRange;
	float m_fTime;
};