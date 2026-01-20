#pragma once

#include "Define.h"
#include "Player.h"

class CPlayer_Origin :public CPlayer
{
public:
	CPlayer_Origin();
	virtual ~CPlayer_Origin();

protected:
	enum ORIGIN_STATE { INHAL_IDLE = 100, INHAL_WALK , INHALTRUE, INHAL_FALSE, ABSORB, ORIGIN_END};

public:
	bool GetInhalKey() { return m_szInhalKeyCheck; }

private:
	void BindAction_INHAL();
	void BindAction_TRANSFORM();

private:
	virtual void BindPressing(int _iKey);

	void BaseAnim(int _iKey);
	void InhalAnim(int _iKey);

	void InhalIDCheck();

protected:
	virtual void KeyInput();
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
	bool m_szInhalKeyCheck;
	bool m_bWater;
	bool m_bInhalCheck;
	float m_fInhalTimer;


};

