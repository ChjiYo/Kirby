#pragma once

#include "Define.h"
#include "Player.h"

class CPlayer_Origin :public CPlayer
{
public:
	CPlayer_Origin();
	virtual ~CPlayer_Origin();

public:
	void LRKey();
	bool GetInhalKey() { return m_szInhalKeyCheck; }
	void WaterMove();
	void Water();

	bool GetWater() { return m_bWater; }

public:
	virtual void MotionChage();
	virtual void Initialize();
	virtual int Update();
	virtual void LateUpdate();
	virtual void Render(HDC _hDC);
	virtual void Release();


private:
	bool m_szInhalKeyCheck;
	bool m_bWater;

};

