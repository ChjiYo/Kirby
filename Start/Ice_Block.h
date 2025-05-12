#pragma once

#include "Define.h"
#include "Attack.h"
class CIce_Block :public CAttack
{
public:
	CIce_Block();
	~CIce_Block();

public:
	virtual const int& GetDamage()const { return m_iDamage; }

	void Land();
	void Touch();
public:
	virtual void Initialize();
	virtual int Update();
	virtual void LateUpdate();
	virtual void Render(HDC _hDC);
	virtual void Release();

	virtual void DamageHit() {};

private:
	float m_fTime;
	bool m_bTouch;
};

