#pragma once

#include "define.h"
#include "Attack.h"

class CStar : public CAttack
{
public:
	CStar();
	virtual ~CStar();

public:
	virtual const int& GetDamage()const { return m_iDamage; }
	void Distory();

public:
	virtual void Initialize();
	virtual int Update();
	virtual void LateUpdate();
	virtual void Render(HDC _hDC);
	virtual void Release();

	virtual void DamageHit();

private:
	float m_fVolume;
};


