#pragma once

#include "define.h"
#include "Player.h"

class CPlayer_Ice :public CPlayer
{
public:
	CPlayer_Ice();
	~CPlayer_Ice();


protected:
	virtual void LRKey();
	virtual void WaterMove();

public:
	virtual void MotionChange();
	virtual void Initialize();
	virtual int Update();
	virtual void LateUpdate();
	virtual void Render(HDC _hDC);
	virtual void Release();

private:
	DWORD m_dwAttackTimer;
};

