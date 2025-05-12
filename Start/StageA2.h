#pragma once

#include "Define.h"
#include "StageA.h"

class CStageA2 :public CStageA
{
public:
	CStageA2();
	~CStageA2();

public:
	virtual void Initialize();
	virtual int Update();
	virtual void LateUpdate();
	virtual void Render(HDC _hDC);
	virtual void Release();
};

