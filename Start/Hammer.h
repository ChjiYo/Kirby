#pragma once

#include "Define.h"
#include "Attack.h"

class CHammer:public CAttack
{
public:
	CHammer();
	~CHammer();

public:
	virtual void MotionChange();
	virtual void Initialize();
	virtual int Update();
	virtual void LateUpdate();
	virtual void Render(HDC _hDC);
	virtual void Release();

	virtual void DamageHit();
};

