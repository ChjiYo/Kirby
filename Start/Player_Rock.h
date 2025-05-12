#pragma once

#include "Define.h"
#include "Player.h"

class CPlayer_Rock :public CPlayer
{
public:
	CPlayer_Rock();
	~CPlayer_Rock();

public:
	virtual void MotionChange();
	void LRKey();

public:
	virtual void Initialize();
	virtual int Update();
	virtual void LateUpdate();
	virtual void Render(HDC _hDC);
	virtual void Release();

private:
	bool StoneStage;
};

