#pragma once

#include "Define.h"
#include "Attack.h"

class CAbilityStar :public CAttack
{
public:
	CAbilityStar();
	~CAbilityStar();

public:
	virtual const int& GetDamage()const { return m_iDamage; }
	void Move();

public:
	virtual void Initialize();
	virtual int Update();
	virtual void LateUpdate();
	virtual void Render(HDC _hDC);
	virtual void Release();

	virtual void DamageHit() {};


private:
	MONID m_MonStarID;

	bool m_bJump;
	float m_fPower;
	float m_fTime;
};

