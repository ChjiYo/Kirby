#pragma once

#include "Define.h"
#include "Player.h"

class CPlayer_Spark :public CPlayer
{
public:
	CPlayer_Spark();
	~CPlayer_Spark();

public:
	void LRKey();

public:
	virtual void MotionChange();
	virtual void Initialize();
	virtual int Update();
	virtual void LateUpdate();
	virtual void Render(HDC _hDC);
	virtual void Release();

private:
	int m_iCopyHp;
	bool m_bAttackCheck;

	DWORD m_dwAttackTimer;
};

