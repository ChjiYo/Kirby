#pragma once

#include "Define.h"
#include "Player.h"

class CPlayer_Sleepy :public CPlayer
{
public:
	CPlayer_Sleepy();
	~CPlayer_Sleepy();

public:
	void Move();

public:
	virtual void MotionChange();
	virtual void Initialize();
	virtual int Update();
	virtual void LateUpdate();
	virtual void Render(HDC _hDC);
	virtual void Release();


};

