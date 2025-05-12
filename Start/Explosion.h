#pragma once

#include "Define.h"
#include "Attack.h"

class CExplosion :public CAttack
{
public:
	enum STATE { EFFECT_IDLE  , EFFECT_BOOM , EFFECT_DISTROY ,STATE_END };

public:
	CExplosion();
	~CExplosion();

	void AnimInst();

public:
	virtual void Initialize();
	virtual int Update();
	virtual void LateUpdate();
	virtual void Render(HDC _hDC);
	virtual void Release();

	virtual void DamageHit() {}

private:
	STATE			m_eCurState;
	STATE			m_ePreState;
};

