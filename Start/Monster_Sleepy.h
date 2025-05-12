#pragma once

#include "define.h"
#include "Monster.h"

class CMonster_Sleepy:public CMonster
{
public:
	CMonster_Sleepy();
	~CMonster_Sleepy();

public:
	void Move();
	void Land();
	virtual void MotionChage() ;


public:
	virtual void Initialize();
	virtual int Update();
	virtual void LateUpdate();
	virtual void Render(HDC _hDC);
	virtual void Release();

private:
	float m_fDistance;
	bool m_bMoveStop;
	float m_fTime;
};

