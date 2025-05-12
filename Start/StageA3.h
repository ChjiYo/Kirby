#pragma once

#include "Define.h"
#include "Scene.h"
#include "StageA.h"

class CStageA3 :public CStageA
{
public:
	CStageA3();
	virtual ~CStageA3();

public:
	virtual void Initialize();
	virtual int Update();
	virtual void LateUpdate();
	virtual void Render(HDC _hDC);
	virtual void Release();
};

